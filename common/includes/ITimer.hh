//
// ITimer.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 23:43:49 2015 chapui_s
// Last update Sun Nov 15 23:43:49 2015 chapui_s
//

#ifndef ITIMER_H_
# define ITIMER_H_

# include <iostream>

# undef min

/**
 * @class  ITimer
 * @brief  Interface pour utiliser la notion de temps
 */

class		ITimer
{
public:
  virtual ~ITimer() {};

  /**
   * Initialise le timer a zero et le lance
   *
   */

  virtual void	start() = 0;

  /**
   * Indique si N millisecondes se sont écoulées depuis start() ( ou reset() )
   *
   * @param long N millisecondes
   *
   * @return true si N millisecondes se sont écoulées. Sinon false
   */

  virtual bool	ms(long) = 0;

  /**
   * Indique combien de millisecondes se sont ecoulées depuis start() ( ou reset() )
   *
   * @return N millisecondes
   */

  virtual long	ms() = 0;

  /**
   * Indique si N nanosecondes se sont écoulées depuis start() ( ou reset() )
   *
   * @param long N nanosecondes
   *
   * @return true si N nanosecondes se sont écoulées. Sinon false
   */

  virtual bool	ns(long) = 0;

  /**
   * Indique combien de nanosecondes se sont ecoulées depuis start() ( ou reset() )
   *
   * @return N nanosecondes
   */

  virtual long	ns() = 0;
  /**
   * Indique si N minutes se sont écoulées depuis start() ( ou reset() )
   *
   * @param long N minutes
   *
   * @return true si N minutes se sont écoulées. Sinon false
   */

  virtual bool	min(long) = 0;

  /**
   * Indique combien de minutes se sont ecoulées depuis start() ( ou reset() )
   *
   * @return N minutes
   */

  virtual long	min() = 0;

  /**
   * Reinitialise le timer a zero et le relance
   *
   */

  virtual void	reset() = 0;
};


#endif /* !ITIMER_H_ */
