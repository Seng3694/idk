#include "idk/core/rectangle.h"
#include <math.h>

bool idk_rectangle_intersects(
    const idk_rect_t *left, const idk_rect_t *right,
    idk_rect_t *outIntersection)
{
    const float interLeft = fmaxf(left->left, right->left);
    const float interTop = fmaxf(left->top, right->top);
    const float interRight =
        fminf(idk_rectangle_right(left), idk_rectangle_right(right));
    const float interBottom =
        fminf(idk_rectangle_bottom(left), idk_rectangle_bottom(right));

    if (interLeft < interRight && interTop < interBottom)
    {
        if (outIntersection != NULL)
            *outIntersection = idk_rectangle_create2(
                interLeft, interTop, interRight, interBottom);
        return true;
    }
    else
    {
        return false;
    }
}
