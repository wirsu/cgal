// Copyright (c) 2004  Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source$
// $Revision$ $Date$
// $Name$
//
// Author(s)     : Niv Sabath
//                 Baruch Zukerman <baruchzu@post.tau.ac.il>

#ifndef POL_NOTIF
#define POL_NOTIF
#include"cgal_types.h"



class Pol_notification : public Pol_arr_change_notification 
{
public:

	//default constructor
	Pol_notification(){}
	
  void add_edge(const  Traits::X_monotone_curve_2 & x_mon_curve,
                Planar_map::Halfedge_handle halfedge_handle, 
                bool  original_direction , bool overlap = false)
  {
   
    //std::cout << "add_edge" << std::endl;

	
	Planar_map::Halfedge_handle he;

	// make sure the halfedge_Handle has the same direction as x_mon_curve
	if( original_direction)
		he = halfedge_handle;
	else
		he = (Planar_map::Halfedge_handle)halfedge_handle->opposite();

	Traits::X_monotone_curve_2 my_x_mon_curve (x_mon_curve);
	Curve_pol_data                 d = x_mon_curve.get_data();

	d.halfedge_handle = he;
	my_x_mon_curve.set_data( d );
	halfedge_handle->set_curve (my_x_mon_curve);
    halfedge_handle->opposite()->set_curve (my_x_mon_curve);

	//std::cout<<" inside notif (add adge) "<< d.halfedge_handle->source()->point()
		//                                  <<" !!!! " << he->source()->point();

    
  }

  void split_edge(Planar_map::Halfedge_handle  orig_edge , 
                  Planar_map::Halfedge_handle  new_edge ,
                  const Traits::X_monotone_curve_2 & c1,
                  const Traits::X_monotone_curve_2 & c2)
  {
    //std::cout << "split_edge" << std::endl;

	Traits::X_monotone_curve_2 my_c1 (c1);
	

	Traits::X_monotone_curve_2 my_c2 (c2);
	
	
	// updating the new curves

	Curve_pol_data d1 = c1.get_data();
	d1.halfedge_handle = orig_edge;
	my_c1.set_data( d1 );   

	Curve_pol_data d2 = c2.get_data();
	d2.halfedge_handle = new_edge;
	my_c2.set_data( d2 );  


	orig_edge->set_curve (my_c1);
    orig_edge->opposite()->set_curve (my_c1);

	new_edge->set_curve (my_c2);
    new_edge->opposite()->set_curve (my_c2);
	
	return;
  }

  void split_face(Planar_map::Face_handle  orig_face , 
                  Planar_map::Face_handle  new_face )
  {
    //std::cout << "split_face" << std::endl;
	new_face->set_info( orig_face->info());  // the new face's color will be the same
											 //as the original face

  }

  void add_hole(Planar_map::Face_handle /* in_face */, 
                Planar_map::Halfedge_handle /* new_hole */)
  {
    //std::cout << "add_hole" << std::endl;
  }

  
};

#endif //POL_NOTIF

