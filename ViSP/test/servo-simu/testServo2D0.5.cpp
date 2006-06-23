

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet Lagadic / IRISA-INRIA Rennes, 2005
 * www  : http://www.irisa.fr/lagadic
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      testServo2D0.5.cpp
 * Project:   ViSP 2.0
 * Author:    Eric Marchand
 *
 * Version control
 * ===============
 *
 *  $Id: testServo2D0.5.cpp,v 1.3 2006-06-23 14:45:07 brenier Exp $
 *
 * Description
 * ============
 *   tests the control law
 *   eye-in-hand control
 *   velocity computed in the camera frame
 *   using theta U visual feature
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*!
  \example testServo2D0.5.cpp
  \brief  test 2 1/2 D visual servoing
*/


#include <visp/vpMath.h>
#include <visp/vpHomogeneousMatrix.h>
#include <visp/vpPoint.h>
#include <visp/vpFeaturePoint.h>
#include <visp/vpFeatureThetaU.h>
#include <visp/vpFeaturePoint3D.h>
#include <visp/vpServo.h>
#include <visp/vpRobotCamera.h>
#include <visp/vpDebug.h>
#include <visp/vpFeatureBuilder.h>

int
main()
{
  vpServo task ;
  vpRobotCamera robot ;

  cout << endl ;
  cout << "-------------------------------------------------------" << endl ;
  cout << " Test program for vpServo "  <<endl ;
  cout << " task :  2 1/2 D visual servoing " << endl ;
  cout << "-------------------------------------------------------" << endl ;
  cout << endl ;


  vpTRACE("sets the initial camera location " ) ;
  vpPoseVector c_r_o(0.1,0.2,2,
		     vpMath::rad(20), vpMath::rad(10),  vpMath::rad(50)
		     ) ;

  vpCTRACE ; cout << endl ;
  vpHomogeneousMatrix cMo(c_r_o) ;
  vpCTRACE ; cout << endl ;
  robot.setPosition(cMo) ;
  vpCTRACE ; cout << endl ;

  vpTRACE("sets the desired camera location " ) ;
  vpPoseVector cd_r_o(0,0,1,
		      vpMath::rad(0),vpMath::rad(0),vpMath::rad(0)) ;
  vpHomogeneousMatrix cdMo(cd_r_o) ;


  vpTRACE("\tsets the point coordinates in the world frame "  ) ;
  vpPoint point ;
  point.setWorldCoordinates(0,0,0) ;
  vpTRACE("\tproject : computes  the point coordinates in the camera frame and its 2D coordinates"  ) ;
  point.track(cMo) ;

  vpPoint pointd ;
  pointd.setWorldCoordinates(0,0,0) ;
  pointd.track(cdMo) ;
  //------------------------------------------------------------------
  vpTRACE("1st feature (x,y)");


  vpTRACE("\t want to it at (0,0)") ;
  vpFeaturePoint p ;
  vpFeatureBuilder::create(p,point)  ;


  vpFeaturePoint pd ;
  vpFeatureBuilder::create(pd,pointd)  ;


  //------------------------------------------------------------------
  vpTRACE("2nd feature (Z)") ;
  vpTRACE("\tnot necessary to project twice (reuse p)") ;
  vpFeaturePoint3D Z ;
  vpFeatureBuilder::create(Z,point)  ;  //retrieve x,y and Z of the vpPoint structure

  vpTRACE("\twant to see it one meter away (here again use pd)") ;
  vpFeaturePoint3D Zd ;
  vpFeatureBuilder::create(Zd,pointd)  ;  //retrieve x,y and Z of the vpPoint structure


  //------------------------------------------------------------------
  vpTRACE("3rd feature ThetaU") ;
  vpTRACE("\tcompute the rotation that the camera has to realize "  ) ;
  vpHomogeneousMatrix cdMc ;
  cdMc = cdMo*cMo.inverse() ;

  vpFeatureThetaU tu ;
  tu.buildFrom(cdMc) ;

  vpTRACE("\tsets the desired rotation (always zero !) ") ;
  vpTRACE("\tsince s is the rotation that the camera has to realize ") ;


  //------------------------------------------------------------------

  vpTRACE("define the task") ;
  vpTRACE("\t we want an eye-in-hand control law") ;
  vpTRACE("\t robot is controlled in the camera frame") ;
  task.setServo(vpServo::EYEINHAND_CAMERA) ;

  task.addFeature(p,pd) ;
  task.addFeature(Z,Zd,vpFeaturePoint3D::selectZ()) ;
  task.addFeature(tu) ;

  vpTRACE("\t set the gain") ;
  task.setLambda(0.1) ;


  vpTRACE("Display task information " ) ;
  task.print() ;

  int iter=0 ;
  vpTRACE("\t loop") ;
  while(iter++<200)
  {
    cout << "---------------------------------------------" << iter <<endl ;
    vpColVector v ;

    if (iter==1) vpTRACE("\t\t get the robot position ") ;
    robot.getPosition(cMo) ;

    if (iter==1) vpTRACE("\t\t update the feature ") ;
    point.track(cMo) ;
    vpFeatureBuilder::create(p,point)  ;
    vpFeatureBuilder::create(Z,point)  ;

    cdMc = cdMo*cMo.inverse() ;
    tu.buildFrom(cdMc) ;


    if (iter==1) vpTRACE("\t\t compute the control law ") ;
    v = task.computeControlLaw() ;
    if (iter==1) task.print() ;

    if (iter==1) vpTRACE("\t\t send the camera velocity to the controller ") ;
    robot.setVelocity(vpRobot::CAMERA_FRAME, v) ;


    cout << task.error.sumSquare() <<endl ; ;
  }

  vpTRACE("Display task information " ) ;
  task.print() ;
  vpTRACE("Final camera location " ) ;
  cout << cMo << endl ;
}

