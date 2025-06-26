#pragma once

#include <format>
#include <optional>
#include <stdexcept>
#include <stacktrace>
#include <type_traits>
#include <source_location>

#include "VyLib/Types.h"
#include "VyLib/Defines.h"


/**
 * @brief Base class for Exceptions.
 */
class Exception : public std::runtime_error
{
    /**
     * std::source_location
     * https://en.cppreference.com/w/cpp/utility/source_location.html
     */
    std::source_location m_Location;

    /**
     * std::stacktrace
     * std::basic_stacktrace<std::allocator<std::stacktrace_entry>> 
     * https://en.cppreference.com/w/cpp/utility/basic_stacktrace.html
     */
    std::stacktrace      m_Trace;

protected:
    /**
     * @brief Exception Initialization.
     * @param message  - The error message.
     * @param location - The source location of the error.
     * @param trace    - The stack trace leading to the error.
     */
    explicit Exception(const String& message, const std::source_location& location, std::stacktrace trace) :
        std::runtime_error(message), m_Location(location), m_Trace(trace)
    {
    }

public:
    Exception(const Exception&)     = default;
    Exception(Exception&&) noexcept = default;

    ~Exception() noexcept override  = default;

    Exception& operator=(const Exception&)     = default;
    Exception& operator=(Exception&&) noexcept = default;

public:
    /**
     * @brief Returns the source location that identifies where the exception has been thrown.
     */
    const std::source_location& location() const noexcept
    {
        return m_Location;
    }

    /**
     * @brief Returns the stack trace leading to the exception.
     */
    const std::stacktrace& trace() const noexcept
    {
        return m_Trace;
    }
};


/**
 * @brief An Exception that is thrown, if a provided argument is invalid.
 */
class InvalidArgumentException : public Exception
{
    String m_Argument;

public:

    /**
     * @brief Initializes a new exception.
     * @param argument - The name of the argument that was invalid.
     */
    explicit InvalidArgumentException(StringView argument) :
        Exception(std::format("Invalid argument provided: {}.", argument), 
        std::source_location::current(), std::stacktrace::current()), m_Argument(argument) 
    {
    }

    /**
     * @brief Initializes a new exception.
     * @param argument - The name of the argument that was invalid.
     * @param message  - The error message.
     */
    explicit InvalidArgumentException(StringView argument, StringView message) :
        Exception(std::format("Invalid argument provided: {}. {}", argument, message), 
        std::source_location::current(), std::stacktrace::current()), m_Argument(argument)
    {
    }

    /**
     * @brief Initializes a new exception.
     * @param argument - The name of the argument that was invalid.
     * @param format   - The format string for the error message.
     * @param args     - The arguments passed to the error message format string.
     */
    template <typename ...TArgs>
    explicit InvalidArgumentException(StringView argument, std::format_string<TArgs...> format, TArgs&&... args) :
        Exception(std::format("Invalid argument provided: {}. {}", argument, std::format(format, std::forward<TArgs>(args)...)), 
        std::source_location::current(), std::stacktrace::current()), m_Argument(argument) 
    {
    }

    InvalidArgumentException(const InvalidArgumentException&)     = default;
    InvalidArgumentException(InvalidArgumentException&&) noexcept = default;

    ~InvalidArgumentException() noexcept override = default;

    InvalidArgumentException& operator=(const InvalidArgumentException&)     = default;
    InvalidArgumentException& operator=(InvalidArgumentException&&) noexcept = default;

public:

    /**
     * @brief Returns the name of the argument that was invalid.
     */
    const String& argument() const noexcept 
    {
        return m_Argument;
    }
};




/**
 * @brief An exception that is thrown, if a provided argument is not within the expected range.
 */
class ArgumentOutOfRangeException : public Exception 
{
    String m_Argument;

public:

    /**
     * @brief Initializes a new exception.
     * @param argument   - The name of the argument that was out of range.
     */
    explicit ArgumentOutOfRangeException(StringView argument) :
        Exception(std::format("Argument was out of range: {}.", argument), 
        std::source_location::current(), std::stacktrace::current()), m_Argument(argument) 
    {
    }

    /**
     * @brief Initializes a new exception.
     * @param argument   - The name of the argument that was out of range.
     * @param message    - The error message.
     */
    explicit ArgumentOutOfRangeException(StringView argument, StringView message) :
        Exception(std::format("Argument was out of range: {}. {}", argument, message), 
        std::source_location::current(), std::stacktrace::current()), m_Argument(argument) 
    {
    }

    /**
     * @brief Initializes a new exception.
     * @param argument   - The name of the argument that was out of range.
     * @param format     - The format string for the error message.
     * @param args       - The arguments passed to the error message format string.
     */
    template <typename ...TArgs>
    explicit ArgumentOutOfRangeException(StringView argument, std::format_string<TArgs...> format, TArgs&&... args) :
        Exception(std::format("Argument was out of range: {}. {}", 
            argument, 
            std::format(format, std::forward<TArgs>(args)...)
        ), 
        std::source_location::current(), std::stacktrace::current()), m_Argument(argument)
    {
    }

    /**
     * @brief Initializes a new exception.
     * @tparam T         - The type of the argument that was out of range.
     * @param argument   - The name of the argument that was out of range.
     * @param validRange - The lower bound and upper bound of the valid range.
     * @param value      - The actual value of provided to the argument.
     * @param format     - The format string for the error message.
     * @param args       - The arguments passed to the error message format string.
     */
    template <typename T, typename ...TArgs>
    explicit ArgumentOutOfRangeException(StringView argument, std::pair<T, T> validRange, T value, std::format_string<TArgs...> format, TArgs&&... args) :
        Exception(std::format("Argument was out of range: {} (valid range is [{}, {}]) but actual value was {}). {}", 
            argument, 
            validRange.first, 
            validRange.second, 
            value, 
            std::format(format, std::forward<TArgs>(args)...)
        ), 
        std::source_location::current(), std::stacktrace::current()), m_Argument(argument) 
    {
    }

    ArgumentOutOfRangeException(const ArgumentOutOfRangeException&)     = default;
    ArgumentOutOfRangeException(ArgumentOutOfRangeException&&) noexcept = default;

    ~ArgumentOutOfRangeException() noexcept override = default;

    ArgumentOutOfRangeException& operator=(const ArgumentOutOfRangeException&)     = default;
    ArgumentOutOfRangeException& operator=(ArgumentOutOfRangeException&&) noexcept = default;

public:
    /**
     * @brief Returns the name of the argument that was out of range.
     */
    const String& argument() const noexcept 
    {
        return m_Argument;
    }
};




/**
 * @brief An exception that is thrown, if a provided non-optional argument was not initialized.
 */
class ArgumentNotInitializedException : public Exception 
{
    String m_Argument;

public:

    /**
     * @brief Initializes a new exception.
     * @param argument - The name of the argument that was not initialized.
     */
    explicit ArgumentNotInitializedException(StringView argument) :
        Exception(std::format("Argument was not initialized: {}.", argument), 
        std::source_location::current(), std::stacktrace::current()), m_Argument(argument) { }

    /**
     * @brief Initializes a new exception.
     * @param argument - The name of the argument that was not initialized.
     * @param message  - The error message.
     */
    explicit ArgumentNotInitializedException(StringView argument, StringView message) :
        Exception(std::format("Argument was not initialized: {}. {}", argument, message), 
        std::source_location::current(), std::stacktrace::current()), m_Argument(argument) { }

    /**
     * @brief Initializes a new exception.
     * @param argument - The name of the argument that was not initialized.
     * @param format   - The format string for the error message.
     * @param args     - The arguments passed to the error message format string.
     */
    template <typename ...TArgs>
    explicit ArgumentNotInitializedException(StringView argument, std::format_string<TArgs...> format, TArgs&&... args) :
        Exception(std::format("Argument was not initialized: {}. {}", argument, std::format(format, std::forward<TArgs>(args)...)),
        std::source_location::current(), std::stacktrace::current()), m_Argument(argument) { }

    
    ArgumentNotInitializedException(const ArgumentNotInitializedException&)     = default;
    ArgumentNotInitializedException(ArgumentNotInitializedException&&) noexcept = default;

    ~ArgumentNotInitializedException() noexcept override = default;

    ArgumentNotInitializedException& operator=(const ArgumentNotInitializedException&)     = default;
    ArgumentNotInitializedException& operator=(ArgumentNotInitializedException&&) noexcept = default;

public:

    /**
     * @brief Returns the name of the argument that was not initialized.
     */
    const String& argument() const noexcept 
    {
        return m_Argument;
    }
};




/**
 * @brief An exception that is thrown, if a requested operation could not be executed.
 */
class RuntimeException : public Exception 
{
public:
    /**
     * @brief Initializes a new exception.
     */
    explicit RuntimeException() :
        Exception("The operation could not be executed.", 
            std::source_location::current(), std::stacktrace::current()) { }

    /**
     * @brief Initializes a new exception.
     * @param message - The error message.
     */
    explicit RuntimeException(StringView message) :
        Exception(std::format("The operation could not be executed: {}", message), 
        std::source_location::current(), std::stacktrace::current()) { }


    /**
     * @brief Initializes a new exception.
     * @param format - The format string for the error message.
     * @param args   - The arguments passed to the error message format string.
     */
    template <typename ...TArgs>
    explicit RuntimeException(std::format_string<TArgs...> format, TArgs&&... args) :
        Exception(std::format("The operation could not be executed: {}", std::format(format, std::forward<TArgs>(args)...)), 
        std::source_location::current(), std::stacktrace::current()) { }


    RuntimeException(const RuntimeException&)     = default;
    RuntimeException(RuntimeException&&) noexcept = default;

    ~RuntimeException() noexcept override = default;

    RuntimeException& operator=(const RuntimeException&)     = default;
    RuntimeException& operator=(RuntimeException&&) noexcept = default;
};
