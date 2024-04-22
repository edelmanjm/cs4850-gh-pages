#include <pybind11/functional.h>
#include <pybind11/operators.h>
#include <pybind11/smart_holder.h>
#include <pybind11/stl.h>

#include <Application.h>
#include <Renderer.h>
#include <ResourceManager.h>
#include <components/LifetimeComponent.h>
#include <components/TextureComponent.h>
#include <components/TransformWrappingComponent.h>
#include <entities/TextEntity.h>
#include <scenes/PythonScene.h>
#include <utility/Geometry.h>

namespace py = pybind11;


/**
 * Needed because SDL_Texture is an incomplete, renderer-specific type.
 * See https://github.com/pybind/pybind11/issues/2770.
 */
struct SDL_Texture_Wrapper {
    std::shared_ptr<SDL_Texture> ptr;
};

/**
 * Needed because SDL_Renderer is an incomplete, renderer-specific type.
 * See https://github.com/pybind/pybind11/issues/2770.
 */
struct SDL_Renderer_Wrapper {
    SDL_Renderer* ptr;
};

// Using progressive mode to reduce verbosity.
// See https://github.com/pybind/pybind11/blob/smart_holder/README_smart_holder.rst
// Example of what we'd need to have otherwise:
// PYBIND11_SMART_HOLDER_TYPE_CASTERS(Renderer)
// ...
// py::class_<Bar, PYBIND11_SH_AVL(Bar)>(m, "Bar"); <-- notice that instead of PYBIND11_SH_DEF it's PYBIND11_SH_AVL

PYBIND11_MAKE_OPAQUE(SDL_Texture);
PYBIND11_MAKE_OPAQUE(SDL_Renderer);

PYBIND11_MODULE(rose, m) {
    m.doc() = "ROSE: Really Open Simple Engine";
    // Could do whyengine or something else punny, but eh

    py::class_<h2d::Point2d>(m, "Point2d").def(py::init<double, double>())
            .def_property("x", &h2d::Point2d::getX, [](h2d::Point2d& p, double x) {
                p.translate(x, 0);
            })
            .def_property("y", &h2d::Point2d::getY, [](h2d::Point2d& p, double y) {
                p.translate(0, y);
            });
    py::class_<h2d::Homogr>(m, "Homogr")
        .def(py::init<>())
        .def("set_translation", &h2d::Homogr::setTranslation<double, double>)
        .def("add_translation", &h2d::Homogr::addTranslation<double>)
        .def("set_rotation", &h2d::Homogr::setRotation<double>)
        .def("add_rotation", &h2d::Homogr::addRotation<double>)
        .def(py::self * h2d::FRect());
    py::class_<h2d::FRect>(m, "FRect")
        .def(py::init<double, double, double, double>())
        .def_property(
            "x", [](h2d::FRect& self) { return Geometry::GetX(self); },
            [](h2d::FRect& self, double x) { Geometry::SetX(self, x); })
        .def_property(
            "y", [](h2d::FRect& self) { return Geometry::GetY(self); },
            [](h2d::FRect& self, double y) { Geometry::SetY(self, y); })
        .def("set", &h2d::FRect::set<float>)
        .def("get_pts", &h2d::FRect::getPts)
        // IDK why this doesn't work but whatever
        //        .def("translate", &h2d::FRect::translate<double, double>)
        .def("translate", [](h2d::FRect& self, double x, double y) { self.translate(x, y); })
        // IDK why this doesn't work either
        //        .def("intersects", &h2d::FRect::intersects<h2d::FRect>)
        .def("move_to", [](h2d::FRect& self, double x, double y) { self.moveTo(x, y); })
        .def("intersects", [](h2d::FRect& self, h2d::FRect& other) { return self.intersects(other)(); });

    py::class_<SDL_FRect>(m, "SDL_FRect")
        .def(py::init<float, float, float, float>())
        .def_readwrite("x", &SDL_FRect::x)
        .def_readwrite("y", &SDL_FRect::y)
        .def_readwrite("w", &SDL_FRect::w)
        .def_readwrite("h", &SDL_FRect::h)
        .def_static("intersects", [](SDL_FRect& foo, SDL_FRect& bar) {
            SDL_FRect result;
            return SDL_GetRectIntersectionFloat(&foo, &bar, &result);
        });
    py::class_<SDL_Color>(m, "SDL_Color")
        .def(py::init<uint8_t, uint8_t, uint8_t, uint8_t>())
        .def_readwrite("r", &SDL_Color::r)
        .def_readwrite("g", &SDL_Color::g)
        .def_readwrite("b", &SDL_Color::b)
        .def_readwrite("a", &SDL_Color::a);
    py::enum_<SDL_Scancode>(m, "SDL_Scancode").export_values();
    py::class_<SDL_Renderer_Wrapper>(m, "SDL_Renderer");
    py::class_<SDL_Texture_Wrapper>(m, "SDL_Texture");

    py::class_<Geometry>(m, "Geometry")
        .def_static("as_sdl", &Geometry::AsSDL)
        .def_static("as_h2d", &Geometry::AsH2D);
    //        .def_static("get_x", &Geometry::GetX)
    //        .def_static("get_y", &Geometry::GetY)
    //        .def_static("set_x", &Geometry::SetX)
    //        .def_static("set_y", &Geometry::SetY);

    py::class_<Renderer, PYBIND11_SH_DEF(Renderer)>(m, "Renderer")
        .def(py::init<int, int>())
        .def_property(
            "wrapped", [](const Renderer& self) { return SDL_Renderer_Wrapper{self.m_Wrapped}; },
            [](Renderer& self, SDL_Renderer_Wrapper wrapped) { self.m_Wrapped = wrapped.ptr; });

    // Using the first method of automatic downcasting
    // See https://pybind11.readthedocs.io/en/stable/classes.html#inheritance-and-automatic-downcasting

    py::class_<Component, PYBIND11_SH_DEF(Component)>(m, "Component");
    py::class_<LifetimeComponent, Component, PYBIND11_SH_DEF(LifetimeComponent)>(m, "LifetimeComponent")
        .def(py::init<uint32_t>());
    py::class_<TextureComponent, Component, PYBIND11_SH_DEF(TextureComponent)>(m, "TextureComponent")
        .def(py::init([](const SDL_Texture_Wrapper& texture, h2d::FRect box) {
            return new TextureComponent(texture.ptr, box);
        }))
        .def("set_texture", [](TextureComponent& self, SDL_Texture_Wrapper texture) {
            self.SetTexture(texture.ptr);
        });
    py::class_<TransformWrappingComponent, Component, PYBIND11_SH_DEF(TransformWrappingComponent)>(m, "TransformWrappingComponent")
        .def(py::init<h2d::FRect>());

    py::class_<GameEntity, PYBIND11_SH_DEF(GameEntity)>(m, "GameEntity")
        .def_readwrite("renderable", &GameEntity::m_Renderable)
        .def("get_transform", [](GameEntity& g) { return g.GetTransform()->m_Transform; })
        .def("set_transform", [](GameEntity& g, const h2d::Homogr& t) { g.GetTransform()->m_Transform = t; })
        .def("get_transformed_origin", &GameEntity::GetTransformedOrigin)
        .def("add_component", &GameEntity::AddComponent<Component>);
    py::class_<CollidingRectangleEntity, GameEntity, PYBIND11_SH_DEF(CollidingRectangleEntity)>(
        m, "CollidingRectangleEntity")
        .def(py::init<>())
        .def("add_required", &CollidingRectangleEntity::AddRequired, py::arg("dims"), py::arg("showBoundingBox") = true)
        .def("set_velocity",
             [](CollidingRectangleEntity& cre, float x, float y) {
                 cre.m_VelocityX = x;
                 cre.m_VelocityY = y;
             })
        .def("get_velocity",
             [](CollidingRectangleEntity& cre) { return py::make_tuple(cre.m_VelocityX, cre.m_VelocityY); })
        .def("rotate", &CollidingRectangleEntity::Rotate)
        .def("get_rotation", &CollidingRectangleEntity::GetRotation)
        .def("add_input_handler", &CollidingRectangleEntity::AddInputHandler)
        .def_static("intersects", &CollidingRectangleEntity::Intersects)
        .def_static("intersects_frect", &CollidingRectangleEntity::IntersectsFRect);
    py::class_<TextEntity, GameEntity, PYBIND11_SH_DEF(TextEntity)>(m, "TextEntity")
        .def(py::init<std::string, uint32_t, SDL_Color>())
        .def("add_required", &TextEntity::AddRequired)
        .def_readwrite("text", &TextEntity::m_Text);

    py::class_<Scene, PYBIND11_SH_DEF(Scene)> scene(m, "Scene");
    py::class_<PythonScene, Scene, PYBIND11_SH_DEF(PythonScene)>(m, "PythonScene")
        .def(py::init<std::shared_ptr<Renderer>>())
        .def("add_entity", &PythonScene::AddEntity)
        .def("remove_entity", &PythonScene::RemoveEntity)
        .def("set_on_update", &PythonScene::SetOnUpdate);

    py::class_<Application>(m, "Application")
        .def(py::init<std::shared_ptr<Renderer>>())
        .def("set_scene", &Application::setScene)
        .def("loop", &Application::Loop);

    py::class_<ResourceManager>(m, "ResourceManager")
        .def_static("load_texture", [](SDL_Renderer_Wrapper renderer, const std::string& filepath) {
            return SDL_Texture_Wrapper{ResourceManager::Instance().LoadTexture(renderer.ptr, filepath)};
        })
        .def_static("load_svg", [](SDL_Renderer_Wrapper renderer, const std::string& svg, float scale = 1.0) {
            return SDL_Texture_Wrapper{ResourceManager::Instance().LoadSvg(renderer.ptr, svg, scale)};
        })
        .def_static("load_image", [](SDL_Renderer_Wrapper renderer, const std::string& filepath) {
            return SDL_Texture_Wrapper{ResourceManager::Instance().LoadImage(renderer.ptr, filepath)};
        });
}