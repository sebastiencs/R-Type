//
// ThreadUnix.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 23:38:28 2015 chapui_s
// Last update Tue Nov 10 23:38:28 2015 chapui_s
//

#ifndef THREADUNIX_H_
# define THREADUNIX_H_

# include <pthread.h>
# include "IThread.hh"

/**
 * @class  ThreadUnix
 * @brief  Implementation de l'interface IThread sous Unix
 * avec la lib pthread
 */

class		ThreadUnix : public IThread
{
private:
  pthread_t	_thread;	/**< Identifiant qui permet de stocker les informations
				   relatives au thread lancé */
  bool		_running;	/**< booleen qui indique si le thread est lancé ou non */

public:
  ThreadUnix();

  /**
   * Constructeur qui permet de lancé directement un thread, la methode run() y est appelée
   *
   * @param func Fonction executée lors de la creation du thread
   * @param arg Parametre donné a la fonction appelé
   *
   * @return true si le thread a bien été créé. Sinon false
   */

  ThreadUnix(const Callback_t &func, void *arg);
  virtual ~ThreadUnix();

  virtual bool	run(const Callback_t &func, void *arg);
  virtual bool	close();
  virtual bool	join();
};

Callback_t	&save_func(const Callback_t &, int);
void		*jump(void *);

#endif /* !THREADUNIX_H_ */
