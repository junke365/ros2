// Copyright (c) 2012, Willow Garage, Inc.
// Copyright (c) 2017, Open Source Robotics Foundation, Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the copyright holder nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.


#include "rviz_common/properties/enum_property.hpp"

#include <string>

#include <QString>  // NOLINT: cpplint is unable to handle the include order here

#include "rviz_common/properties/combo_box.hpp"

namespace rviz_common
{
namespace properties
{

EnumProperty::EnumProperty(
  const QString & name,
  const QString & default_value,
  const QString & description,
  Property * parent,
  const char * changed_slot,
  QObject * receiver)
: StringProperty(name, default_value, description, parent, changed_slot, receiver)
{
}

void EnumProperty::clearOptions()
{
  strings_.clear();
  ints_.clear();
}

void EnumProperty::addOption(const QString & option, int value)
{
  strings_.push_back(option);
  ints_[option] = value;
}

int EnumProperty::getOptionInt()
{
  QString current_string = getValue().toString();
  QHash<QString, int>::const_iterator int_iter = ints_.find(current_string);
  if (int_iter != ints_.end() ) {
    return int_iter.value();
  }
  return 0;
}

void EnumProperty::addOptionStd(const std::string & option, int value)
{
  addOption(QString::fromStdString(option), value);
}

QWidget * EnumProperty::createEditor(QWidget * parent, const QStyleOptionViewItem & option)
{
  Q_UNUSED(option);
  // Emit requestOptions() to give listeners a chance to change the option list.
  Q_EMIT requestOptions(this);

  ComboBox * cb = new ComboBox(parent);
  cb->addItems(strings_);
  cb->setCurrentIndex(strings_.indexOf(getValue().toString() ));
  QObject::connect(
    cb, SIGNAL(currentIndexChanged(const QString&)), this,
    SLOT(setString(const QString&)));

  // TODO(anyone): need to better handle string value which is not in list.
  return cb;
}

void EnumProperty::setString(const QString & str)
{
  setValue(str);
}

void EnumProperty::setStringStd(const std::string & str)
{
  setString(QString::fromStdString(str));
}

void EnumProperty::sortOptions()
{
  strings_.sort();
}

}  // namespace properties
}  // namespace rviz_common
