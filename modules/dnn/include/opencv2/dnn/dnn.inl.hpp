#ifndef __OPENCV_DNN_INL_HPP__
#define __OPENCV_DNN_INL_HPP__

#include <opencv2/dnn.hpp>

namespace cv
{
namespace dnn
{
    inline Mat& Blob::getMatRef()
    {
        return m;
    }

    inline const Mat& Blob::getMatRef() const
    {
        return m;
    }

    inline Mat Blob::getMat()
    {
        return m;
    }

    inline Mat Blob::getMat(int num, int channel)
    {
        CV_Assert(0 <= num && num < this->num() && 0 <= channel && channel < this->channels());
        return Mat(rows(), cols(), m.type(), this->rawPtr(num, channel));
    }

    inline int Blob::cols() const
    {
        CV_DbgAssert(m.dims > 2);
        return m.size[m.dims-1];
    }

    inline int Blob::rows() const
    {
        CV_DbgAssert(m.dims > 2);
        return m.size[m.dims-2];
    }

    inline Size Blob::size() const
    {
        return Size(cols(), rows());
    }
    
    inline int Blob::channels() const
    {
        CV_DbgAssert(m.dims >= 3);
        return m.size[m.dims-3];
    }
    
    inline int Blob::num() const
    {
        CV_DbgAssert(m.dims == 4);
        return m.size[0];
    }

    inline Vec4i Blob::shape() const
    {
        CV_DbgAssert(m.dims == 4);
        return Vec4i(m.size.p);
    }

    inline size_t Blob::total() const
    {
        CV_DbgAssert(m.dims == 4);
        return (size_t) m.size[0] * m.size[1] * m.size[2] * m.size[3];
    }

    inline uchar* Blob::rawPtr(int num, int cn, int row, int col)
    {
        CV_DbgAssert(m.dims == 4);
        return m.data + num * m.step[0] + cn * m.step[1] + row * m.step[2] + col * m.step[3];
    }

    template<typename TFloat>
    TFloat *Blob::ptr(int num, int cn, int row, int col)
    {
        CV_Assert(m.type() == cv::DataType<TFloat>::type && m.dims == 4);
        return (TFloat*) rawPtr(num, cn, row, col);
    }

}
}

#endif