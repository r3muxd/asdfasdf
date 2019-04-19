#include "Esp.h"
#include "../Interfaces.h"
#include "../SDK/Vector.h"

static bool screenTransform(const Vector& in, Vector& out) noexcept
{
    static auto& matrix = interfaces.engine->worldToScreenMatrix();

    out.x = matrix[0][0] * in.x + matrix[0][1] * in.y + matrix[0][2] * in.z + matrix[0][3];
    out.y = matrix[1][0] * in.x + matrix[1][1] * in.y + matrix[1][2] * in.z + matrix[1][3];
    out.z = 0.0f;

    float w = matrix[3][0] * in.x + matrix[3][1] * in.y + matrix[3][2] * in.z + matrix[3][3];

    if (w < 0.001f) {
        out.x *= 100000;
        out.y *= 100000;
        return false;
    }

    out.x /= w;
    out.y /= w;
    return true;
}

static bool worldToScreen(const Vector& in, Vector& out) noexcept
{
    if (screenTransform(in, out)) {
        const auto [width, height] = interfaces.surface->getScreenSize();

        out.x = (width / 2.0f) + (out.x * width) / 2.0f;
        out.y = (height / 2.0f) - (out.y * height) / 2.0f;

        return true;
    }
    return false;
}

void Esp::render() noexcept
{

}
