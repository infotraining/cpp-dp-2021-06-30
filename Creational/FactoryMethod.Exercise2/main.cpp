#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "shape.hpp"
#include "shape_factories.hpp"

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;

class GraphicsDoc
{
    vector<unique_ptr<Shape>> shapes_;
    ShapeFactory& shape_factory_;
    ShapeRWFactory& shape_rw_factory_;

public:
    GraphicsDoc(ShapeFactory& shape_factory, ShapeRWFactory& shape_rw_factory)
        : shape_factory_{shape_factory}
        , shape_rw_factory_{shape_rw_factory}
    {
    }

    void add(unique_ptr<Shape> shp)
    {
        shapes_.push_back(move(shp));
    }

    void render()
    {
        for (const auto& shp : shapes_)
            shp->draw();
    }

    void load(const string& filename)
    {
        ifstream file_in{filename};

        if (!file_in)
        {
            cout << "File not found!" << endl;
            exit(1);
        }

        while (file_in)
        {
            string shape_id;
            file_in >> shape_id;

            if (!file_in)
                return;

            cout << "Loading " << shape_id << "..." << endl;

            auto shape = shape_factory_.create(shape_id);
            auto shape_rw = shape_rw_factory_.create(make_type_index(*shape));

            shape_rw->read(*shape, file_in);

            shapes_.push_back(move(shape));
        }
    }

    void save(const string& filename)
    {
        ofstream file_out{filename};

        for (const auto& shp : shapes_)
        {
            auto shape_rw = shape_rw_factory_.create(make_type_index(*shp));
            shape_rw->write(*shp, file_out);
        }
    }
};

int main()
{
    cout << "Start..." << endl;

    // ShapeFactory shape_factory;
    // shape_factory.register_creator(Drawing::Rectangle::id, std::make_unique<Rectangle>);
    // shape_factory.register_creator(Drawing::Square::id, std::make_unique<Square>);
    // shape_factory.register_creator(Drawing::Circle::id, std::make_unique<Circle>);

    // ShapeRWFactory shape_rw_factory;
    // shape_rw_factory.register_creator(make_type_index<Drawing::Rectangle>(), std::make_unique<Drawing::IO::RectangleReaderWriter>);
    // shape_rw_factory.register_creator(make_type_index<Drawing::Square>(), std::make_unique<Drawing::IO::SquareReaderWriter>);
    // shape_rw_factory.register_creator(make_type_index<Drawing::Circle>(), std::make_unique<Drawing::IO::CircleReaderWriter>);

    GraphicsDoc doc(SingletonShapeFactory::instance(), SingletonShapeRWFactory::instance());

    doc.load("drawing.txt");

    cout << "\n";

    doc.render();

    doc.save("new_drawing.txt");
}
