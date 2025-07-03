#pragma once

#define VY_NO_COPY(Class)         Class(const Class&) = delete; Class& operator=(const Class&) = delete;

#define VY_NO_MOVE(Class)         Class(Class&&) = delete; Class& operator=(Class&&) = delete;

#define VY_STATIC_CLASS(Class)    Class() = delete; ~Class() = delete;

#define VY_SINGLETON_CLASS(Class) Class(Class& Copy) = delete; Class operator=(Class& copy) = delete;
