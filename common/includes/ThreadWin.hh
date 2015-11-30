//
// ThreadWin.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:39:16 2015 chapui_s
// Last update Wed Nov 11 15:39:16 2015 chapui_s
//

#ifndef THREADWIN_H_
# define THREADWIN_H_

# include "SocketsWin.hh"
# include "IThread.hh"

/**
 * @class  ThreadWin
 * @brief  Implementation de l'interface IThread sous Windows
 */

class		ThreadWin : public IThread
{
private:
  HANDLE	_thread;	/**< Identifiant qui permet de stocker les informations
				   relatives au thread lancé */
  bool		_running;	/**< booleen qui indique si le thread est lancé ou non */

public:
  ThreadWin();

  /**
   * Constructeur qui permet de lancé directement un thread, la methode run() y est appelée
   *
   * @param func Fonction executée lors de la creation du thread
   * @param arg Parametre donné a la fonction appelé
   *
   * @return true si le thread a bien été créé. Sinon false
   */

  ThreadWin(const Callback_t &, void *);
  virtual ~ThreadWin();

  virtual bool	run(const Callback_t &, void *);
  virtual bool	close();
  virtual bool	join();
};

Callback_t	&save_func(const Callback_t &, int);
void		*jump(void *);

#endif /* !THREADWIN_H_ */
