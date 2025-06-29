; ModuleID = 'apf.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@0 = private unnamed_addr constant [30 x i8] c"I am your dad,\E6\88\91\E6\98\AF\E4\BD\A0\E7\88\B8!\\n\00", align 1
@.str = private unnamed_addr constant [3 x i8] c"%s\00", align 1

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

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local i32 @"\E8\BE\93\E5\87\BA"(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = call i32 (ptr, ...) @printf(ptr noundef @.str, ptr noundef %3)
  ret i32 %4
}

declare i32 @printf(ptr noundef, ...) #1

attributes #0 = { mustprogress noinline optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.ident = !{!0}
!llvm.module.flags = !{!1, !2, !3, !4, !5}

!0 = !{!"Ubuntu clang version 18.1.8 (11~20.04.2)"}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{i32 7, !"frame-pointer", i32 2}
