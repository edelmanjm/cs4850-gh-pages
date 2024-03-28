#include <pybind11/functional.h>
#include <pybind11/smart_holder.h>

#include <Application.h>
#include <Renderer.h>
#include <scenes/PythonScene.h>

namespace py = pybind11;

// Using progressive mode to reduce verbosity.
// See https://github.com/pybind/pybind11/blob/smart_holder/README_smart_holder.rst
// Example of what we'd need to have otherwise:
// PYBIND11_SMART_HOLDER_TYPE_CASTERS(Renderer)
// ...
// py::class_<Bar, PYBIND11_SH_AVL(Bar)>(m, "Bar"); <-- notice that instead of PYBIND11_SH_DEF it's PYBIND11_SH_AVL

PYBIND11_MODULE(rose, m) {
    m.doc() = "ROSE: Really Open Simple Engine";
    // Could do whyengine or something else punny, but eh

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

    py::class_<Renderer, PYBIND11_SH_DEF(Renderer)>(m, "Renderer")
        .def(py::init<int, int>());

    // Using the first method of automatic downcasting
    // See https://pybind11.readthedocs.io/en/stable/classes.html#inheritance-and-automatic-downcasting

    py::class_<GameEntity, PYBIND11_SH_DEF(GameEntity)> (m, "GameEntity")
        .def("get_transform", [](GameEntity& g) {
            return g.GetTransform()->m_Rectangle;
        });
    py::class_<CollidingRectangleEntity,
               GameEntity, PYBIND11_SH_DEF(CollidingRectangleEntity)>(m, "CollidingRectangleEntity")
        .def(py::init<>())
        .def("add_required", &CollidingRectangleEntity::AddRequired)
        .def("set_velocity", &CollidingRectangleEntity::SetVelocity)
        .def_static("intersects", &CollidingRectangleEntity::Intersects);

    py::class_<Scene, PYBIND11_SH_DEF(Scene)> scene(m, "Scene");
    py::class_<PythonScene, Scene, PYBIND11_SH_DEF(PythonScene)>(m, "PythonScene")
        .def(py::init<std::shared_ptr<Renderer>>())
        .def("add_entity", &PythonScene::AddEntity)
        .def("set_on_update", &PythonScene::SetOnUpdate);

    py::class_<Application>(m, "Application")
        .def(py::init<std::shared_ptr<Renderer>>())
        .def("set_scene", &Application::setScene)
        .def("loop", &Application::Loop);
}