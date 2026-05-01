#pragma once
#include "NativeWrapper.h"
#include <mapbox/compatibility/value.hpp>

namespace DOTNET_NAMESPACE
{
    /// <summary>
    /// A variant type representing a JSON-like value: null, boolean, string, signed or unsigned
    /// integer, double, array, or object. Used for feature properties and style expression evaluation.
    /// </summary>
    public ref class Value : NativeWrapper<mapbox::base::Value>
    {
    public:
        /// <summary>Initializes a null <see cref="Value" />.</summary>
        Value();
        /// <summary>Initializes a boolean <see cref="Value" />.</summary>
        Value(System::Boolean v);
        /// <summary>Initializes a string <see cref="Value" />.</summary>
        Value(System::String^ str);
        /// <summary>Initializes a signed 8-bit integer <see cref="Value" />.</summary>
        Value(System::SByte n);
        /// <summary>Initializes a signed 16-bit integer <see cref="Value" />.</summary>
        Value(System::Int16 n);
        /// <summary>Initializes a signed 32-bit integer <see cref="Value" />.</summary>
        Value(System::Int32 n);
        /// <summary>Initializes a signed 64-bit integer <see cref="Value" />.</summary>
        Value(System::Int64 n);
        /// <summary>Initializes an unsigned 8-bit integer <see cref="Value" />.</summary>
        Value(System::Byte n);
        /// <summary>Initializes an unsigned 16-bit integer <see cref="Value" />.</summary>
        Value(System::UInt16 n);
        /// <summary>Initializes an unsigned 32-bit integer <see cref="Value" />.</summary>
        Value(System::UInt32 n);
        /// <summary>Initializes an unsigned 64-bit integer <see cref="Value" />.</summary>
        Value(System::UInt64 n);
        /// <summary>Initializes a single-precision float <see cref="Value" /> (stored as double).</summary>
        Value(System::Single n);
        /// <summary>Initializes a double-precision float <see cref="Value" />.</summary>
        Value(System::Double n);
        /// <summary>Initializes an array <see cref="Value" /> from a sequence of values.</summary>
        Value(System::Collections::Generic::IEnumerable<Value^>^ a);
        /// <summary>Initializes an object <see cref="Value" /> from a string-keyed dictionary.</summary>
        Value(System::Collections::Generic::IDictionary<System::String^, Value^>^ o);
        ~Value();

        /// <summary>Returns the value as a signed 64-bit integer, or <see langword="null" /> if the held type is not a signed integer.</summary>
        System::Nullable<System::Int64> GetInt();
        /// <summary>Returns the value as an unsigned 64-bit integer, or <see langword="null" /> if the held type is not an unsigned integer.</summary>
        System::Nullable<System::UInt64> GetUInt();
        /// <summary>Returns the value as a boolean, or <see langword="null" /> if the held type is not a boolean.</summary>
        System::Nullable<System::Boolean> GetBool();
        /// <summary>Returns the value as a double, or <see langword="null" /> if the held type is not a number.</summary>
        System::Nullable<System::Double> GetDouble();
        /// <summary>Returns the array elements, or <see langword="null" /> if the held type is not an array.</summary>
        System::Collections::Generic::IEnumerable<Value^>^ GetArray();
        /// <summary>Returns the object members, or <see langword="null" /> if the held type is not an object.</summary>
        System::Collections::Generic::IDictionary<System::String^, Value^>^ GetObject();
        /// <summary>Returns the value as a string, or <see langword="null" /> if the held type is not a string.</summary>
        System::String^ GetString();

        /// <summary>Returns <see langword="true" /> when the value is non-null and non-zero.</summary>
        explicit operator bool();
    internal:
        Value(NativePointerHolder<mapbox::base::Value>^ nativePointerHolder);
    };
}
