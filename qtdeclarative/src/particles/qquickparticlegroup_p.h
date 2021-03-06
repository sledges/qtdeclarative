/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtQuick module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef QQuickPARTICLEGROUP
#define QQuickPARTICLEGROUP
#include <private/qquickspriteengine_p.h>
#include "qquickparticlesystem_p.h"
#include "qqmlparserstatus.h"

QT_BEGIN_NAMESPACE

class QQuickParticleGroup : public QQuickStochasticState, public QQmlParserStatus
{
    Q_OBJECT
    //### Would setting limits per group be useful? Or clutter the API?
    //Q_PROPERTY(int maximumAlive READ maximumAlive WRITE setMaximumAlive NOTIFY maximumAliveChanged)

    Q_PROPERTY(QQuickParticleSystem* system READ system WRITE setSystem NOTIFY systemChanged)

    //Intercept children requests and assign to the group & system
    Q_PROPERTY(QQmlListProperty<QObject> particleChildren READ particleChildren DESIGNABLE false)//### Hidden property for in-state system definitions - ought not to be used in actual "Sprite" states
    Q_CLASSINFO("DefaultProperty", "particleChildren")
    Q_INTERFACES(QQmlParserStatus)

public:
    explicit QQuickParticleGroup(QObject* parent = 0);

    QQmlListProperty<QObject> particleChildren();

    int maximumAlive() const
    {
        return m_maximumAlive;
    }

    QQuickParticleSystem* system() const
    {
        return m_system;
    }

public slots:

    void setMaximumAlive(int arg)
    {
        if (m_maximumAlive != arg) {
            m_maximumAlive = arg;
            emit maximumAliveChanged(arg);
        }
    }

    void setSystem(QQuickParticleSystem* arg);

    void delayRedirect(QObject* obj);

signals:

    void maximumAliveChanged(int arg);

    void systemChanged(QQuickParticleSystem* arg);

protected:
    virtual void componentComplete();
    virtual void classBegin(){;}

private:

    void performDelayedRedirects();

    int m_maximumAlive;
    QQuickParticleSystem* m_system;
    QList<QObject*> m_delayedRedirects;
};

QT_END_NAMESPACE

#endif
