cmake_minimum_required(VERSION 3.10)
project(SamiERPEngine)

# تحديد إصدار اللغة
set(CMAKE_CXX_STANDARD 11)

# تعريف الملفات المطلوبة للبرنامج
add_executable(SamiERPEngine main.cpp httplib.h)

# ربط مكتبة الـ Threads لأن السيرفر بيعتمد عليها
find_package(Threads REQUIRED)
target_link_libraries(SamiERPEngine Threads::Threads)