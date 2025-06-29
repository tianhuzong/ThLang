; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [30 x i8] c"I am your dad,\E6\88\91\E6\98\AF\E4\BD\A0\E7\88\B8!\n\00", align 1

define i32 @"\E5\8A\A0\E6\B3\95"(i32 %a, i32 %b) {
entry:
  %a.addr = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  %b.addr = alloca i32, align 4
  store i32 %b, ptr %b.addr, align 4
  %0 = load i32, ptr %a.addr, align 4
  %1 = load i32, ptr %b.addr, align 4
  %addtmp = add i32 %0, %1
  ret i32 %addtmp
}

declare i32 @"\E8\BE\93\E5\87\BA"(ptr)

define i32 @main() {
entry:
  %0 = alloca i32, align 4
  store i32 0, ptr %0, align 4
  %1 = alloca ptr, align 8
  store ptr @0, ptr %1, align 8
  %2 = load ptr, ptr %1, align 8
  %calltmp = call i32 @"\E8\BE\93\E5\87\BA"(ptr %2)
  %3 = load i32, ptr %0, align 4
  ret i32 %3
}

