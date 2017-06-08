program test

	use iso_c_binding, only: c_ptr, c_f_pointer, c_char, c_null_ptr, c_float, c_loc
	
!TYPE :: t_gt_wrapper
!	TYPE(C_PTR) :: gt_wrapper_ptr = C_NULL_PTR
!END TYPE t_gt_wrapper
	
	
	implicit none
	type(C_PTR) :: c_p
	real, target :: dim(3)
! 	type(c_ptr), pointer :: cptr_a

	interface
		function gt_wrapper_create(name) bind(c)
			USE, INTRINSIC :: iso_c_binding
			implicit none
			type(c_ptr) :: gt_wrapper_create
			CHARACTER(KIND=C_CHAR), DIMENSION(*) :: name
		end function gt_wrapper_create
	end interface
	
!	interface
!		SUBROUTINE gt_wrapper_call(action) bind(c)
!			USE, INTRINSIC :: iso_c_binding
!			implicit none
!			CHARACTER(KIND=C_CHAR), DIMENSION(*) :: action
!		end SUBROUTINE gt_wrapper_call
!	end interface
	
	INTERFACE
     SUBROUTINE gt_wrapper_call(wrapper, action) &
          BIND(c, name='gt_wrapper_call')
       USE, INTRINSIC :: iso_c_binding
       TYPE(C_PTR), INTENT(IN), VALUE       :: wrapper
       CHARACTER(KIND=C_CHAR), DIMENSION(*) :: action
     END SUBROUTINE gt_wrapper_call
    END INTERFACE
    
	INTERFACE
     SUBROUTINE gt_wrapper_call_proc(wrapper, action, data) &
          BIND(c, name='gt_wrapper_call_proc')
       USE, INTRINSIC :: iso_c_binding
       TYPE(C_PTR), INTENT(IN), VALUE       :: wrapper, data
       CHARACTER(KIND=C_CHAR), DIMENSION(*) :: action
     END SUBROUTINE gt_wrapper_call_proc
    END INTERFACE
	
	c_p = gt_wrapper_create("dycore")	
	 print *, "fortran: wrapper ok"
	
	call gt_wrapper_call(c_p,"some_action")	
	call gt_wrapper_call(c_p,"some_action2")	
	

	dim(1)=3.1415
	dim(2)=3.1416
	dim(3)=3.1417
	print *, "a in fortran: ", dim(1)
	
!	ptr_a =>a
!	cptr_a = C_LOC(a)
	
	call gt_wrapper_call_proc(c_p, "pass_int", C_LOC(dim))

end