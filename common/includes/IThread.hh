//
// IThread.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 23:32:53 2015 chapui_s
// Last update Tue Nov 10 23:32:53 2015 chapui_s
//

#ifndef ITHREAD_H_
# define ITHREAD_H_

# include <functional>
# include "Debug.hh"

typedef std::function<void *(void *)>	Callback_t;

/**
 * @class  IThread
 * @brief  Interface pour utiliser des threads
 */

class		IThread
{
public:
  virtual ~IThread() {};

/**
 *
 * Methode qui permet de lancer un nouveau thread en lui donnant
 * un argument
 *
 * @param func Fonction executée lors de la creation du thread
 * @param arg Parametre donné a la fonction appelé
 *
 * @return true si le thread a bien été créé. Sinon false
 */

  virtual bool	run(const Callback_t &func, void *arg) = 0;

  /**
   * Methode qui permet de fermer et quitter le thread immédiatement
   *
   * @return true si le thread a bien quitté. False dans le cas contraire
   */

  virtual bool	close() = 0;

  /**
   * Methode qui permet d'attendre la fin d'execution du thread
   *
   * @return true si le thread a bien quitté. False dans le cas contraire
   */

  virtual bool	join() = 0;
};

#endif /* !ITHREAD_H_ */
