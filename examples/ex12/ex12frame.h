#ifndef EX12F_H
#define EX12F_H

#include <QAbstractVideoSurface>

class Ex12frame : public QAbstractVideoSurface
{
Q_OBJECT
public:
    Ex12frame(QObject* parent=0);
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    bool present(const QVideoFrame &frame);
signals:
    void frameAvailable(QImage frame);
};

#endif
