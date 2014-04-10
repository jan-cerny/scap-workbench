/*
 * Copyright 2014 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Martin Preisler <mpreisle@redhat.com>
 */

#include "RemoteMachineComboBox.h"

RemoteMachineComboBox::RemoteMachineComboBox(QWidget* parent):
    QWidget(parent)
{
    mUI.setupUi(this);

#if (QT_VERSION >= QT_VERSION_CHECK(4, 7, 0))
    // placeholder text is only supported in Qt 4.7 onwards
    mUI.host->setPlaceholderText("username@hostname");
#endif
}

RemoteMachineComboBox::~RemoteMachineComboBox()
{}

QString RemoteMachineComboBox::getTarget() const
{
    return QString("%1:%2").arg(mUI.host->text()).arg(mUI.port->value());
}
