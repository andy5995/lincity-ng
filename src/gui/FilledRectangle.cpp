/*
Copyright (C) 2005 Matthias Braun <matze@braunis.de>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/**
 * @author Matthias Braun
 * @file FilledRectangle.cpp
 */

#include <string.h>              // for strcmp
#include <iostream>              // for char_traits, operator<<, basic_ostream

#include "ComponentFactory.hpp"  // for IMPLEMENT_COMPONENT_FACTORY
#include "FilledRectangle.hpp"
#include "Painter.hpp"           // for Painter
#include "Rect2D.hpp"            // for Rect2D
#include "XmlReader.hpp"         // for XmlReader

FilledRectangle::FilledRectangle()
{}

FilledRectangle::~FilledRectangle()
{}

void
FilledRectangle::parse(XmlReader& reader)
{
    XmlReader::AttributeIterator iter(reader);
    while(iter.next()) {
        const char* attribute = (const char*) iter.getName();
        const char* value = (const char*) iter.getValue();

        if(parseAttribute(attribute, value)) {
            continue;
        } else if (strcmp(attribute, "color") == 0) {
            color.parse(value);
        } else {
            std::cerr << "Unknown attribute '" << attribute
                      << "' in FilledRectangle.\n";
        }
    }

    flags |= FLAG_RESIZABLE;
}

void
FilledRectangle::resize(float width, float height)
{
    if(width < 0) width = 0;
    if(height < 0) height = 0;
    this->width = width;
    this->height = height;
}

void
FilledRectangle::draw(Painter& painter)
{
    painter.setFillColor(color);
    painter.fillRectangle(Rect2D(0, 0, width, height));
}

IMPLEMENT_COMPONENT_FACTORY(FilledRectangle)

/** @file gui/FilledRectangle.cpp */
