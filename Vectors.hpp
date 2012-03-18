#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <cstring>
#include <cmath>

namespace CGE
{
    template<typename T, size_t N>
    inline void copyVectors(const T inSource[], T inDestination[])
    {
        memcpy(inDestination, inSource, N * sizeof(T));
    }

    template<typename T, size_t N>
    void addVectors(const T inLVector[], const T inRVector[], T inAnswer[])
    {
        for (size_t i = 0; i < N; ++i)
            inAnswer[i] = inLVector[i] + inRVector[i];
    }

    template<typename T, size_t N>
    void subtractVectors(const T inLVector[], const T inRVector[], T inAnswer[])
    {
        for (size_t i = 0; i < N; ++i)
            inAnswer[i] = inLVector[i] - inRVector[i];
    }

    template<typename T>
    inline T lengthSquared2(const T inVector[])
    {
        return inVector[0] * inVector[0] + inVector[1] * inVector[1];
    }

    template<typename T>
    inline T lengthSquared3(const T inVector[])
    {
        return inVector[0] * inVector[0] + inVector[1] * inVector[1] +
            inVector[2] * inVector[2];
    }

    template<typename T>
    T length2(const T inVector[])
    {
        return sqrt(lengthSquared2(inVector));
    }

    template<typename T>
    T length3(const T inVector[])
    {
        return sqrt(lengthSquared3(inVector));
    }

    template<typename T>
    void normalize2(T inVector[], T inLength = static_cast<T>(1))
    {
        inLength /= length2(inVector);
        inVector[0] *= inLength;
        inVector[1] *= inLength;
    }

    template<typename T>
    void normalize3(T inVector[], T inLength = static_cast<T>(1))
    {
        inLength /= length3(inVector);
        inVector[0] *= inLength;
        inVector[1] *= inLength;
        inVector[2] *= inLength;
    }

    template<typename T>
    void cross(const T inLVector[], const T inRVector[], T inAnswer[])
    {
        inAnswer[0] = inLVector[1] * inRVector[2] - inLVector[2] * inRVector[1];
        inAnswer[1] = inLVector[2] * inRVector[0] - inLVector[0] * inRVector[2];
        inAnswer[2] = inLVector[0] * inRVector[1] - inLVector[1] * inRVector[0];
    }

    template<typename T>
    T dot(const T inLVector[], const T inRVector[])
    {
        return inLVector[0] * inRVector[0]
            + inLVector[1] * inRVector[1]
            + inLVector[2] * inRVector[2];
    }

    /// /// /// new vector object /// /// ///

    template<typename T, size_t N>
    class Vector
    {
        public:
            inline Vector() { memset(mData, 0, sizeof(T) * N); }
            inline Vector(const Vector& inVector)
            {
                memcpy(mData, inVector.mData, sizeof(T) * N);
            }

            inline Vector(const T* inVector)
            {
                memcpy(mData, inVector, sizeof(T) * N);
            }

            inline ~Vector() {}

            inline operator T*() { return mData; }
            inline operator const T*() const { return mData; }

            inline T* getData() { return mData; }

            inline Vector& operator=(const T* inVector)
            {
                memcpy(mData, inVector, sizeof(T) * N);
                return *this;
            }

            Vector& operator+=(const T* inVector)
            {
                Vector v(*this);
                addVectors<T, N>(v, inVector, mData);
                return *this;
            }

        private:
            T mData[N];
    };
}

typedef CGE::Vector<float, 2> vec2f;
typedef CGE::Vector<float, 3> vec3f;
typedef CGE::Vector<float, 4> vec4f;

typedef CGE::Vector<double, 2> vec2d;
typedef CGE::Vector<double, 3> vec3d;
typedef CGE::Vector<double, 4> vec4d;

#endif
