/***************************************************************************
 *   Copyright (C) 2003 by Julian Rockey                                   *
 *   linux@jrockey.com                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/



#ifndef __KDEVPART_FILECREATE_FILEDIALOG_H__
#define __KDEVPART_FILECREATE_FILEDIALOG_H__

#include <kfiledialog.h>

namespace FileCreate {

  class FileDialog : public KFileDialog {

  public:
    FileDialog(const QString& startDir, const QString& filter,
               QWidget *parent, const char *name,
               bool modal, QWidget * extraWidget);
    virtual ~FileDialog();

    virtual void initGUI();

  
  };

}

#endif
