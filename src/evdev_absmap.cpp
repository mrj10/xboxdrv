/*
**  Xbox360 USB Gamepad Userspace Driver
**  Copyright (C) 2010 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "evdev_absmap.hpp"

#include "controller_message.hpp"
#include "helper.hpp"

EvdevAbsMap::EvdevAbsMap() :
  m_plus_map(),
  m_minus_map(),
  m_both_map()
{
}

void
EvdevAbsMap::bind_plus(int code, int axis)
{
  m_plus_map[code] = axis;
}

void
EvdevAbsMap::bind_minus(int code, int axis)
{
   m_minus_map[code] = axis; 
}

void
EvdevAbsMap::bind_both(int code, int axis)
{
  m_both_map[code] = axis; 
}

void
EvdevAbsMap::clear()
{
  m_plus_map.clear();
  m_minus_map.clear();
  m_both_map.clear();
}

void
EvdevAbsMap::process(ControllerMessage& msg, int code, int value, int min, int max) const
{
  { // process plus map
    std::map<int, int>::const_iterator it = m_plus_map.find(code);
    if (it != m_plus_map.end())
    {
      // '+ 1' so that we round up, instead of round down 
      const int center = (max - min + 1) / 2;
      const float v = to_float(value, center, min);
      msg.set_abs_float(it->second, v); 
    }
  }

  { // process minus map
    std::map<int, int>::const_iterator it = m_minus_map.find(code);
    if (it != m_minus_map.end())
    {
      // '+ 1' so that we round up, instead of round down 
      const int center = (max - min + 1) / 2;
      const float v = to_float(value, center, max);
      msg.set_abs_float(it->second, v);
    }
  }

  { // process both map
    std::map<int, int>::const_iterator it = m_both_map.find(code);
    if (it != m_both_map.end())
    {
      const float v = to_float(value, min, max);
      msg.set_abs_float(it->second, v); 
    }
  }
}

/* EOF */
