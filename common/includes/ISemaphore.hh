//
// ISemaphore.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 18 22:13:17 2015 chapui_s
// Last update Wed Nov 18 22:13:17 2015 chapui_s
//

#ifndef ISEMAPHORE_H_
# define ISEMAPHORE_H_

/**
 * @class  ISemaphore
 * @brief  Interface pour utiliser une semaphore
 */

class		ISemaphore
{
public:
  virtual ~ISemaphore() {};

/**
 * Methode qui incremente la semaphore.\n
 * Si le compteur etait a zero et qu'un autre processus/thread
 * restait bloqué sur wait(), alors ca le debloque
 *
 *
 * @return true si l'incrementation s'est bien déroulé.
 * Sinon retourne false
 */

  virtual bool	post() = 0;

/**
 * Methode qui essaye de decrementer la semaphore\n
 * Si le compteur etait a zero, le compteur ne change pas
 * et la fonction retourne immédiatement
 *
 *
 * @return true si le compteur a bien été decrementé. Sinon false
 */

  virtual bool	tryWait() = 0;

/**
 * Methode qui decremente la semaphore.\n
 * Si le compteur etait a zero, le thread/processus reste bloqué
 * dans la fonction tant que la semaphore n'a pas été incrementé
 * par un autre thread/processus.\n
 * Si le compteur etait supérieur a zero, alors la fonction wait
 * retourne immédiatement.
 *
 *
 * @return true si tout s'est bien passé
 */

  virtual bool	wait() = 0;
};

#endif /* !ISEMAPHORE_H_ */
