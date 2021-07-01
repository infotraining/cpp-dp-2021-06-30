#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "rectangle.hpp"

namespace Drawing
{
    class Square : public Shape
    {
        Rectangle rect_;

    public:
        static constexpr const char* id = "Square";

        Square(int x = 0, int y = 0, int size = 0);

        Point coord() const;

        void set_coord(const Point& pt);

        int size() const;

        void set_size(int size);

        void draw() const override;

        void move(int dx, int dy) override;

        std::unique_ptr<Shape> clone() const override
        {
            return std::make_unique<Square>(*this); // copy constructor of Rectangle called by make_unique
        }
    };
}

#endif // SQUARE_HPP
