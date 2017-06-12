PROGRAM cpp_dycore

USE m_gt_wrapper
USE iso_c_binding

TYPE(t_gt_wrapper) :: dycore_wrapper
INTEGER, TARGET :: dim(3)

call gt_wrapper_create(dycore_wrapper,"dycore")


dim(1)=3
dim(2)=4
dim(3)=5
print *, "[Fortran] dim: ", dim(1), dim(2), dim(3)

call gt_wrapper_call_proc(dycore_wrapper, "pass_int", C_LOC(dim))

print *, "[Fortran] dim: ", dim(1), dim(2), dim(3)

call gt_wrapper_call(dycore_wrapper,"some_action")	
call gt_wrapper_call(dycore_wrapper,"some_action2")

call gt_wrapper_call_proc(dycore_wrapper, "pass_int", C_LOC(dim))

END PROGRAM cpp_dycore
