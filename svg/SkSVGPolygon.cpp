/* libs/graphics/svg/SkSVGPolygon.cpp
**
** Copyright 2006, Google Inc.
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#include "SkSVGPolygon.h"
#include "SkSVGParser.h"

const SkSVGAttribute SkSVGPolygon::gAttributes[] = {
    SVG_LITERAL_ATTRIBUTE(clip-rule, f_clipRule),
    SVG_LITERAL_ATTRIBUTE(fill-rule, f_fillRule),
    SVG_ATTRIBUTE(points)
};

DEFINE_SVG_INFO(Polygon)

void SkSVGPolygon::addAttribute(SkSVGParser& parser, int attrIndex, 
        const char* attrValue, size_t attrLength) {
    INHERITED::addAttribute(parser, attrIndex, attrValue, attrLength);
}

void SkSVGPolygon::translate(SkSVGParser& parser, bool defState) {
    parser._startElement("polygon");
    SkSVGElement::translate(parser, defState);
    SVG_ADD_ATTRIBUTE(points);
    if (f_fillRule.size() > 0) 
        parser._addAttribute("fillType", f_fillRule.equals("evenodd") ? "evenOdd" : "winding");
    parser._endElement();
}
