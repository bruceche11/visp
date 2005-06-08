
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet Lagadic / IRISA-INRIA Rennes, 2005
 * www  : http://www.irisa.fr/lagadic
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      vpRobotException.h
 * Project:   ViSP2
 * Author:    Eric Marchand
 *
 * Version control
 * ===============
 *
 *  $Id: vpRobotException.h,v 1.1.1.1 2005-06-08 07:08:09 fspindle Exp $
 *
 * Description
 * ============
 *  error that can be emited by the vpRobot class and its derivates
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#ifndef __vpRobotException_H
#define __vpRobotException_H


/* ------------------------------------------------------------------------- */
/* --- INCLUDE ------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */


/* \file vpRobotException.h
   \brief error that can be emited by the vpRobot class and its derivates
 */
/* Classes standards. */
using namespace std;
#include <iostream>                /* Classe ostream.    */
#include <string>                  /* Classe string.     */
#include <visp/vpException.h>

/* ------------------------------------------------------------------------- */
/* --- CLASS --------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

/* \brief error that can be emited by the vpRobot class and its derivates
 */
class vpRobotException : public vpException
{
public:
  /*!
    \brief Lists the possible error than can be emmited while calling
    vpRobot member
   */
  enum errorRobotCodeEnum
    {

	    /** Erreur lancee par le constructor. */
	    ERRConstruction,

	    /** Erreur lancee lors de la construction d'un objet CRobot
	     * correspondant a un robot reel si l'objet de la classe en
	     * question doit etre unique. */
	    ERRUniqueRobot,

	    /** Erreur lancee par les fonctions de commande si le
	     * robot n'est pas dans le bon etat au moment du passage
	     * d'ordre. */
	    ERRWrongState,

	    /** Erreur lancee par les fonctions de changement d'etat
	     * si le changement demandee n'est pas possible. */
	    ERRStateModification,

	    /** Erreur generee lors d'un retour non nulle d'une fonction
	     * de communication de la lib Afma6. */
	    ERRCommunication,

	    /** Erreur lancee apres un appel a une fonction de la lib
	     * bas-niveau de control de l'afma6 ayant renvoye une erreur. */
	    ERRLowLevel,

	    /** Erreur lancee par la fonction de parsing des parametres du
	     * robot, si le fichier donne en entree n'est pas valide.
	     */
	    ERRReadingParameters,

	    /** Erreur lancee par les methodes d'une classe qui necessite
	     * un appel a une fonction d'initialisation apres la
	     * construction si l'init n'a pas ete fait. */
	    ERRNotInitialized,

	    /** Erreur lancee par les fonctions decrites dans lAPI mais
	     * pas completement implementee. Dans ce cas, la fonction
	     * affiche simplement un message d'erreur avant de sortir
	     * par le 'throw'.
	     */
	    ERRNotImplemented
    } ;

public:
  vpRobotException (const int code, const char * msg)
    : vpException(code, msg){ ; }
  vpRobotException (const int code, const string & msg)
    : vpException(code, msg){ ; }
  vpRobotException (const int code)
    : vpException(code){ ; }

};





#endif /* #ifndef __vpRobotException_H */


/*
 * Local variables:
 * c-basic-offset: 2
 * End:
 */
