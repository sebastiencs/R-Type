//
// Timer.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 23:47:35 2015 chapui_s
// Last update Sun Nov 15 23:47:35 2015 chapui_s
//

#include <iostream>
#include "Timer.hh"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void		Timer::start()
{
  _t = std::chrono::high_resolution_clock::now();
}

void		Timer::reset()
{
  start();
}

bool		Timer::ms(long ms)
{
  std::chrono::high_resolution_clock::time_point	t2;
  t2 = std::chrono::high_resolution_clock::now();

  std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - _t);

  return ((diff.count() >= ms) ? (true) : (false));
}

long		Timer::ms()
{
  std::chrono::high_resolution_clock::time_point	t2;
  t2 = std::chrono::high_resolution_clock::now();

  std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - _t);

  return (static_cast<long>(diff.count()));
}

bool		Timer::ns(long ms)
{
  std::chrono::high_resolution_clock::time_point	t2;
  t2 = std::chrono::high_resolution_clock::now();

  std::chrono::nanoseconds diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - _t);

  return ((diff.count() >= ms) ? (true) : (false));
}

long		Timer::ns()
{
  std::chrono::high_resolution_clock::time_point	t2;
  t2 = std::chrono::high_resolution_clock::now();

  std::chrono::nanoseconds diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - _t);

  return (static_cast<long>(diff.count()));
}

bool		Timer::min(long ms)
{
  std::chrono::high_resolution_clock::time_point	t2;
  t2 = std::chrono::high_resolution_clock::now();

  std::chrono::minutes diff = std::chrono::duration_cast<std::chrono::minutes>(t2 - _t);

  return ((diff.count() >= ms) ? (true) : (false));
}

long		Timer::min()
{
  std::chrono::high_resolution_clock::time_point	t2;
  t2 = std::chrono::high_resolution_clock::now();

  std::chrono::minutes diff = std::chrono::duration_cast<std::chrono::minutes>(t2 - _t);

  return (diff.count());
}