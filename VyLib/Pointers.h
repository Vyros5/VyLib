#pragma once

#include <memory>


/// @brief Represents a unique pointer, that expresses exclusive ownership.
/// @tparam T        - The type of the object the pointer points to.
/// @tparam TDeleter - The deleter for the pointed object.
template<class T, class TDeleter = std::default_delete<T>>
using UniquePtr = std::unique_ptr<T, TDeleter>;


/// @brief Creates a new unique pointer.
/// @tparam T - The type of the object, the pointer points to.
/// @return A new unique pointer.
template <class T>
[[nodiscard]] constexpr UniquePtr<T> MakeUnique() 
{
return std::make_unique<T>();
}


/// @brief Creates a new unique pointer.
/// @tparam T        - The type of the object, the pointer points to
/// @tparam ...TArgs 
/// @param ..._args 
/// @return A new unique pointer.
template <class T, class... TArgs>
[[nodiscard]] constexpr UniquePtr<T> MakeUnique(TArgs&&... _args) 
{
    return std::make_unique<T>(std::forward<TArgs>(_args)...);
}



/// @brief Represents a shared pointer, that expresses non-exclusive ownership.
/// @tparam T - The type of the object the pointer points to.
template <class T>
using SharedPtr = std::shared_ptr<T>;


/// @brief Creates a new shared pointer.
/// @tparam T - The type of the object, the pointer points to.
/// @return A new shared pointer.
template <class T>
[[nodiscard]] constexpr SharedPtr<T> MakeShared() 
{
    return std::make_shared<T>();
}


/// @brief Creates a new shared pointer.
/// @tparam T        - The type of the object, the pointer points to.
/// @tparam ...TArgs 
/// @param ..._args 
/// @return A new shared pointer.
template <class T, class... TArgs>
[[nodiscard]] constexpr SharedPtr<T> MakeShared(TArgs&&... _args) 
{
    return std::make_shared<T>(std::forward<TArgs>(_args)...);
}



/// @brief Transfers a unique pointer to a shared pointer. The unique pointer will be released during this process.
/// @tparam T  - The type of the object, the pointer points to.
/// @param ptr - The unique pointer that should be turned into a shared pointer.
/// @return A new shared pointer.
template <class T>
[[nodiscard]] constexpr SharedPtr<T> AsShared(UniquePtr<T>&& ptr) 
{
    SharedPtr<T> shared = std::move(ptr);
    return shared;
}



/// @brief Represents a weak pointer, that expresses a reference to a shared pointer instance.
/// @tparam T - The type of the object the pointer points to.
template <class T>
using WeakPtr = std::weak_ptr<T>;
