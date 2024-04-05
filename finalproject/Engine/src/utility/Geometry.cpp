#include <utility/Geometry.h>

std::optional<SDL_FRect> Geometry::AsSDL(h2d::FRect& r) {
    auto points = r.get4Pts();
    if (points[0].getX() == points[1].getX()) {
        return SDL_FRect{static_cast<float>(points[0].getX()), static_cast<float>(points[0].getY()),
                         static_cast<float>(r.height()), static_cast<float>(r.width())};
    } else {
        return std::nullopt;
    }
}

double Geometry::GetX(h2d::FRect& r) {
    return r.getPts().first.getX();
}

double Geometry::GetY(h2d::FRect& r) {
    return r.getPts().first.getY();
}

void Geometry::SetX(h2d::FRect& r, double x) {
    auto smallest = r.getPts().first;
    r.moveTo(x, smallest.getY());
}

void Geometry::SetY(h2d::FRect& r, double y) {
    auto smallest = r.getPts().first;
    r.moveTo(smallest.getX(), y);
}
