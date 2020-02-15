//
//  Ex12frame Widget
//

#include "ex12frame.h"

//
// Constructor
//
Ex12frame::Ex12frame(QObject*parent) :
    QAbstractVideoSurface(parent)
{
}

//
//  Must reimplement supported pixel formats
//  These must be convertable to a QImage
//
QList<QVideoFrame::PixelFormat> Ex12frame::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    Q_UNUSED(handleType);
    return QList<QVideoFrame::PixelFormat>()
        << QVideoFrame::Format_ARGB32
        << QVideoFrame::Format_ARGB32_Premultiplied
        << QVideoFrame::Format_RGB32
        << QVideoFrame::Format_RGB24
        << QVideoFrame::Format_RGB565
        << QVideoFrame::Format_RGB555
        << QVideoFrame::Format_ARGB8565_Premultiplied
        << QVideoFrame::Format_BGRA32
        << QVideoFrame::Format_BGRA32_Premultiplied
        << QVideoFrame::Format_BGR32
        << QVideoFrame::Format_BGR24
        << QVideoFrame::Format_BGR565
        << QVideoFrame::Format_BGR555
        << QVideoFrame::Format_BGRA5658_Premultiplied
        << QVideoFrame::Format_NV12
        << QVideoFrame::Format_NV21
        << QVideoFrame::Format_IMC1
        << QVideoFrame::Format_IMC2
        << QVideoFrame::Format_IMC3
        << QVideoFrame::Format_IMC4
        << QVideoFrame::Format_Y8
        << QVideoFrame::Format_Y16
        << QVideoFrame::Format_Jpeg
        << QVideoFrame::Format_CameraRaw
        << QVideoFrame::Format_AdobeDng;
}

//
//    Must reimplement frame present
//
bool Ex12frame::present(const QVideoFrame &frame)
{
   //  Ensure that frame is valid
   if (!frame.isValid()) return false;
   //  Clone video frame to CPU RAM
   QVideoFrame clone(frame);
   if (!clone.map(QAbstractVideoBuffer::ReadOnly)) return false;
   //  Create image from clone
   const QImage image(clone.bits(),clone.width(),clone.height(),
                      QVideoFrame::imageFormatFromPixelFormat(clone.pixelFormat()));
   //  Unmap clone
   clone.unmap();
   //  Make sure the image is valid
   if (image.isNull()) return false;
   //  Emit image
   emit frameAvailable(image);
   return true;
}
