//
// ThreadWin.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:47:25 2015 chapui_s
// Last update Wed Nov 11 15:47:26 2015 chapui_s
//

#include "ThreadWin.hh"

ThreadWin::ThreadWin()
{
}

ThreadWin::ThreadWin(const std::function<void *(void *)> &func, void *arg = 0)
{
  run(func, arg);
}

ThreadWin::~ThreadWin()
{
}

bool	ThreadWin::run(const std::function<void *(void *)> &func, void *arg = 0)
{
}

std::function<void *(void *)>	&save_func(const std::function<void *(void *)> &func = 0, int save = 0)
{
  return (0);
}

void	*jump(void *arg)
{
  return (0);
}

bool	ThreadWin::close()
{
  return (true);
}

bool	ThreadWin::join()
{
  return (true);
}
