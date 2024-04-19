#include <utility/Geometry.h>

SDL_FRect Geometry::AsSDL(h2d::FRect r) {
    auto points = r.getPts();
    return SDL_FRect{static_cast<float>(points.first.getX()), static_cast<float>(points.first.getY()),
                     static_cast<float>(r.width()), static_cast<float>(r.height())};
}

h2d::FRect Geometry::AsH2D(SDL_FRect r) {
    return {r.x, r.y, r.x + r.w, r.y + r.h};
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

double Geometry::ApproximateRotation(h2d::Homogr transform) {
    h2d::Line2d unit(0, 0, 1, 0);
    h2d::Line2d applied = transform * unit;
    return applied.getAngle(unit);
}