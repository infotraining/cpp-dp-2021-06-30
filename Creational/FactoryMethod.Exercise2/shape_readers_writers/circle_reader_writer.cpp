#include "circle_reader_writer.hpp"
#include "../shape_factories.hpp"
#include "../circle.hpp"

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;


// TODO - register CircleReaderWriter creator in a factory
namespace 
{
    bool is_registered = SingletonShapeRWFactory::instance().register_creator(make_type_index<Drawing::Circle>(), std::make_unique<Drawing::IO::CircleReaderWriter>);
}

void CircleReaderWriter::read(Shape& shp, istream& in)
{
    Circle& sqr = static_cast<Circle&>(shp);

    Point pt;
    int r;

    in >> pt >> r;

    sqr.set_radius(r);
    sqr.set_coord(pt);
}

void CircleReaderWriter::write(const Shape& shp, ostream& out)
{
    const Circle& square = dynamic_cast<const Circle&>(shp);

    out << Circle::id << " " << square.coord() << " " << square.radius() << endl;
}
