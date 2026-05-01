#pragma once
#include "NativeWrapper.h"
#include <mbgl/util/vectors.hpp>
#include <mbgl/util/mat4.hpp>

namespace DOTNET_NAMESPACE
{
    ref class Mat4;

    /// <summary>A 3-component column vector of doubles. Implements <see cref="System::Collections::Generic::IReadOnlyList{T}" /> for index access.</summary>
    public ref class Vec3 : NativeWrapper<mbgl::vec3>, System::Collections::Generic::IReadOnlyList<System::Double>
    {
    public:
        /// <summary>Initializes a zero <see cref="Vec3" />.</summary>
        Vec3();
        ~Vec3();

        virtual System::Collections::Generic::IEnumerator<System::Double>^ GetEnumerator();
        virtual System::Collections::IEnumerator^ GetEnumeratorObject() = System::Collections::IEnumerable::GetEnumerator;

        /// <summary>Gets or sets the component at the specified index (0, 1, or 2).</summary>
        property System::Double default[System::Int32] { virtual System::Double get(System::Int32 index); System::Void set(System::Int32 index, System::Double value); };
        /// <summary>Gets the number of components (always 3).</summary>
        property System::Int32 Count { virtual System::Int32 get(); }
    internal:
        Vec3(NativePointerHolder<mbgl::vec3>^ nativePointerHolder);
    };

    /// <summary>A 4-component column vector of doubles. Implements <see cref="System::Collections::Generic::IReadOnlyList{T}" /> for index access.</summary>
    public ref class Vec4 : NativeWrapper<mbgl::vec4>, System::Collections::Generic::IReadOnlyList<System::Double>
    {
    public:
        /// <summary>Initializes a zero <see cref="Vec4" />.</summary>
        Vec4();
        ~Vec4();

        virtual System::Collections::Generic::IEnumerator<System::Double>^ GetEnumerator();
        virtual System::Collections::IEnumerator^ GetEnumeratorObject() = System::Collections::IEnumerable::GetEnumerator;

        /// <summary>Gets or sets the component at the specified index (0, 1, 2, or 3).</summary>
        property System::Double default[System::Int32] { virtual System::Double get(System::Int32 index); System::Void set(System::Int32 index, System::Double value); };
        /// <summary>Gets the number of components (always 4).</summary>
        property System::Int32 Count { virtual System::Int32 get(); }

        /// <summary>Transforms <paramref name="out" /> in-place by matrix <paramref name="m" />.</summary>
        static System::Void TransformMat4(Vec4^ out, Mat4^ m);
        /// <summary>Transforms vector <paramref name="a" /> by matrix <paramref name="m" /> and stores the result in <paramref name="out" />.</summary>
        static System::Void TransformMat4(Vec4^ out, Vec4^ a, Mat4^ m);
    internal:
        Vec4(NativePointerHolder<mbgl::vec4>^ nativePointerHolder);
    };

    /// <summary>
    /// A 4x4 column-major matrix of doubles. Implements <see cref="System::Collections::Generic::IReadOnlyList{T}" /> for flat
    /// index access (16 elements, column-major order).
    /// </summary>
    public ref class Mat4 : NativeWrapper<mbgl::mat4>, System::Collections::Generic::IReadOnlyList<System::Double>
    {
    public:
        /// <summary>Initializes an identity <see cref="Mat4" />.</summary>
        Mat4();
        /// <summary>Initializes a <see cref="Mat4" /> by copying <paramref name="source" />.</summary>
        Mat4(Mat4^ source);
        ~Mat4();

        virtual System::Collections::Generic::IEnumerator<System::Double>^ GetEnumerator();
        virtual System::Collections::IEnumerator^ GetEnumeratorObject() = System::Collections::IEnumerable::GetEnumerator;

        /// <summary>Gets or sets the element at the specified flat index (0–15, column-major).</summary>
        property System::Double default[System::Int32] { virtual System::Double get(System::Int32 index); System::Void set(System::Int32 index, System::Double value); };
        /// <summary>Gets the number of elements (always 16).</summary>
        property System::Int32 Count { virtual System::Int32 get(); }

        /// <summary>Sets <paramref name="out" /> to the identity matrix.</summary>
        static System::Void Identity(Mat4^ out);
        /// <summary>Inverts <paramref name="out" /> in-place. Returns <see langword="false" /> if the matrix is singular.</summary>
        static System::Boolean Invert(Mat4^ out);
        /// <summary>Inverts <paramref name="a" /> and stores the result in <paramref name="out" />. Returns <see langword="false" /> if the matrix is singular.</summary>
        static System::Boolean Invert(Mat4^ out, Mat4^ a);
        /// <summary>Generates an orthographic projection matrix into <paramref name="out" />.</summary>
        static System::Void Ortho(Mat4^ out, System::Double left, System::Double right, System::Double bottom, System::Double top, System::Double near, System::Double far);
        /// <summary>Generates a perspective projection matrix into <paramref name="out" />.</summary>
        /// <param name="fovy">Vertical field of view in radians.</param>
        /// <param name="aspect">Aspect ratio (width / height).</param>
        static System::Void Perspective(Mat4^ out, System::Double fovy, System::Double aspect, System::Double near, System::Double far);
        /// <summary>Copies matrix <paramref name="a" /> into <paramref name="out" />.</summary>
        static System::Void Copy(Mat4^ out, Mat4^ a);
        /// <summary>Translates <paramref name="out" /> in-place by (x, y, z).</summary>
        static System::Void Translate(Mat4^ out, System::Double x, System::Double y, System::Double z);
        /// <summary>Translates matrix <paramref name="a" /> by (x, y, z) and stores the result in <paramref name="out" />.</summary>
        static System::Void Translate(Mat4^ out, Mat4^ a, System::Double x, System::Double y, System::Double z);
        /// <summary>Rotates <paramref name="out" /> in-place around the X axis by <paramref name="rad" /> radians.</summary>
        static System::Void RotateX(Mat4^ out, System::Double rad);
        /// <summary>Rotates matrix <paramref name="a" /> around the X axis and stores the result in <paramref name="out" />.</summary>
        static System::Void RotateX(Mat4^ out, Mat4^ a, System::Double rad);
        /// <summary>Rotates <paramref name="out" /> in-place around the Y axis by <paramref name="rad" /> radians.</summary>
        static System::Void RotateY(Mat4^ out, System::Double rad);
        /// <summary>Rotates matrix <paramref name="a" /> around the Y axis and stores the result in <paramref name="out" />.</summary>
        static System::Void RotateY(Mat4^ out, Mat4^ a, System::Double rad);
        /// <summary>Rotates <paramref name="out" /> in-place around the Z axis by <paramref name="rad" /> radians.</summary>
        static System::Void RotateZ(Mat4^ out, System::Double rad);
        /// <summary>Rotates matrix <paramref name="a" /> around the Z axis and stores the result in <paramref name="out" />.</summary>
        static System::Void RotateZ(Mat4^ out, Mat4^ a, System::Double rad);
        /// <summary>Scales <paramref name="out" /> in-place by (x, y, z).</summary>
        static System::Void Scale(Mat4^ out, System::Double x, System::Double y, System::Double z);
        /// <summary>Scales matrix <paramref name="a" /> by (x, y, z) and stores the result in <paramref name="out" />.</summary>
        static System::Void Scale(Mat4^ out, Mat4^ a, System::Double x, System::Double y, System::Double z);
        /// <summary>Post-multiplies <paramref name="out" /> in-place by <paramref name="a" />.</summary>
        static System::Void Multiply(Mat4^ out, Mat4^ a);
        /// <summary>Multiplies <paramref name="a" /> by <paramref name="b" /> and stores the result in <paramref name="out" />.</summary>
        static System::Void Multiply(Mat4^ out, Mat4^ a, Mat4^ b);
    internal:
        Mat4(NativePointerHolder<mbgl::mat4>^ nativePointerHolder);
    };

    /// <summary>
    /// Extension methods for <see cref="Mat4" /> and <see cref="Vec4" /> that expose the same matrix
    /// operations as instance-style calls (e.g. <c>mat.Multiply(other)</c>).
    /// </summary>
    [System::Runtime::CompilerServices::ExtensionAttribute]
    public ref class MatrixExtensions abstract sealed
    {
    public:
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Identity(Mat4^ out);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Boolean Invert(Mat4^ out);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Boolean Invert(Mat4^ out, Mat4^ a);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Ortho(Mat4^ out, System::Double left, System::Double right, System::Double bottom, System::Double top, System::Double near, System::Double far);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Perspective(Mat4^ out, System::Double fovy, System::Double aspect, System::Double near, System::Double far);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Copy(Mat4^ out, Mat4^ a);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Translate(Mat4^ out, System::Double x, System::Double y, System::Double z);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Translate(Mat4^ out, Mat4^ a, System::Double x, System::Double y, System::Double z);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void RotateX(Mat4^ out, System::Double rad);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void RotateX(Mat4^ out, Mat4^ a, System::Double rad);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void RotateY(Mat4^ out, System::Double rad);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void RotateY(Mat4^ out, Mat4^ a, System::Double rad);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void RotateZ(Mat4^ out, System::Double rad);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void RotateZ(Mat4^ out, Mat4^ a, System::Double rad);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Scale(Mat4^ out, System::Double x, System::Double y, System::Double z);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Scale(Mat4^ out, Mat4^ a, System::Double x, System::Double y, System::Double z);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Multiply(Mat4^ out, Mat4^ a);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Multiply(Mat4^ out, Mat4^ a, Mat4^ b);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void TransformMat4(Vec4^ out, Mat4^ m);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void TransformMat4(Vec4^ out, Vec4^ a, Mat4^ m);
    };
}
