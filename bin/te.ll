; ModuleID = 'main'
source_filename = "main"

define i32 @main() {
entry:
  %0 = alloca i32, align 4
  store i32 0, ptr %0, align 4
  %1 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  %2 = load i32, ptr %0, align 4
  %cmptmp = icmp eq i32 %2, 1
  br i1 %cmptmp, label %then, label %else

then:                                             ; preds = %entry
  %3 = load i32, ptr %0, align 4
  %subtmp = sub i32 %3, 1
  store i32 %subtmp, ptr %1, align 4
  br label %ifcont

else:                                             ; preds = %entry
  br i1 true, label %then1, label %else2

then1:                                            ; preds = %else
  %4 = load i32, ptr %0, align 4
  store i32 %4, ptr %1, align 4
  br label %ifcont

else2:                                            ; preds = %else
  br label %ifcont

ifcont:                                           ; preds = %else2, %then1
  %5 = load i32, ptr %1, align 4
  ret i32 %5
}
