MODULE m_gt_wrapper

USE iso_c_binding

IMPLICIT NONE

PUBLIC :: &
  t_gt_wrapper, &
  gt_wrapper_create, &
  gt_wrapper_call, &
  gt_wrapper_call_proc

PRIVATE

  TYPE :: t_gt_wrapper
    TYPE(C_PTR) :: gt_wrapper_ptr = C_NULL_PTR
  END TYPE t_gt_wrapper
  
CONTAINS

SUBROUTINE gt_wrapper_create(gt_wrapper,name)
  USE iso_c_binding, ONLY: C_F_POINTER
  
  CHARACTER(LEN=*), INTENT(IN)    :: name
  TYPE(t_gt_wrapper), INTENT(OUT) :: gt_wrapper
  
  INTERFACE
    FUNCTION gt_wrapper_create_(name) &
        BIND(c, name='gt_wrapper_create')
      USE, INTRINSIC :: iso_c_binding
      TYPE(C_PTR)                          :: gt_wrapper_create_
      CHARACTER(KIND=C_CHAR), DIMENSION(*) :: name
    END FUNCTION gt_wrapper_create_
  END INTERFACE

  TYPE(C_PTR) :: c_gt_wrapper
  
  c_gt_wrapper = gt_wrapper_create_(TRIM(name)//C_NULL_CHAR)
  gt_wrapper%gt_wrapper_ptr = c_gt_wrapper
  
END SUBROUTINE gt_wrapper_create

SUBROUTINE gt_wrapper_call(gt_wrapper,action)
  USE iso_c_binding, ONLY: C_F_POINTER
  
  TYPE(t_gt_wrapper), INTENT(INOUT) :: gt_wrapper
  CHARACTER(LEN=*), INTENT(IN)      :: action
  
  
  INTERFACE
    FUNCTION gt_wrapper_call_(gt_wrapper,action) &
        BIND(c, name='gt_wrapper_call')
      USE, INTRINSIC :: iso_c_binding
      INTEGER                              :: gt_wrapper_call_
      TYPE(C_PTR), VALUE                   :: gt_wrapper
      CHARACTER(KIND=C_CHAR), DIMENSION(*) :: action
    END FUNCTION gt_wrapper_call_
  END INTERFACE

  INTEGER :: error_code
  error_code = gt_wrapper_call_(gt_wrapper%gt_wrapper_ptr, TRIM(action)//C_NULL_CHAR)
END SUBROUTINE gt_wrapper_call

SUBROUTINE gt_wrapper_call_proc(gt_wrapper,action,data)
  USE iso_c_binding, ONLY: C_F_POINTER
  
  TYPE(t_gt_wrapper), INTENT(INOUT) :: gt_wrapper
  CHARACTER(LEN=*), INTENT(IN)      :: action
  TYPE(C_PTR), INTENT(IN)           :: data
  
  INTERFACE
    ! should be function and use the error_code if we cannot use INOUT on data
    FUNCTION gt_wrapper_call_proc_(gt_wrapper,action,data) &
        BIND(c, name='gt_wrapper_call_proc')
      USE, INTRINSIC :: iso_c_binding
      INTEGER                              :: gt_wrapper_call_proc_
      TYPE(C_PTR), VALUE                   :: gt_wrapper, data
      CHARACTER(KIND=C_CHAR), DIMENSION(*) :: action
    END FUNCTION gt_wrapper_call_proc_
  END INTERFACE

  INTEGER :: error_code
  error_code = gt_wrapper_call_proc_(gt_wrapper%gt_wrapper_ptr, TRIM(action)//C_NULL_CHAR, data)
END SUBROUTINE gt_wrapper_call_proc

END MODULE m_gt_wrapper
