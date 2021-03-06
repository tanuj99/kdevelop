/*
 * This file is part of KDevelop
 *
 * Copyright 2016 Carlos Nihelton <carlosnsoliveira@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef CLANGTIDY_JOB_H
#define CLANGTIDY_JOB_H

// plugin
#include "parsers/clangtidyparser.h"
#include <debug.h>
// KDevPlatform
#include <interfaces/iproblem.h>
#include <outputview/outputexecutejob.h>

namespace ClangTidy
{
/**
 * \class
 * \brief specializes a KJob for running clang-tidy.
 */
class Job : public KDevelop::OutputExecuteJob
{
    Q_OBJECT

public:
    /**
     * \class
     * \brief command line parameters.
     */
    struct Parameters {
        QString projectRootDir;
        QString executablePath;
        QStringList filePaths;
        QString buildDir;
        QString additionalParameters;
        QString enabledChecks;
        bool useConfigFile = false;
        QString headerFilter;
        bool checkSystemHeaders = false;
        int parallelJobCount = 1;
    };

    explicit Job(const Parameters& params, QObject* parent = nullptr);
    ~Job() override;

public: // KJob API
    void start() override;

Q_SIGNALS:
    void problemsDetected(const QVector<KDevelop::IProblem::Ptr>& problems);

protected Q_SLOTS:
    void postProcessStdout(const QStringList& lines) override;
    void postProcessStderr(const QStringList& lines) override;

    void childProcessExited(int exitCode, QProcess::ExitStatus exitStatus) override;
    void childProcessError(QProcess::ProcessError processError) override;

protected:
    void processStdoutLines(const QStringList& lines);
    void processStderrLines(const QStringList& lines);

private:
    void generateMakefile();

protected:
    ClangTidyParser m_parser;
    QStringList m_standardOutput;
    QStringList m_xmlOutput;
    const Job::Parameters m_parameters;
    QString m_makeFilePath;
    int m_finishedCount = 0;
    int m_totalCount = 0;

    QVector<KDevelop::IProblem::Ptr> m_problems;
};

}

#endif
