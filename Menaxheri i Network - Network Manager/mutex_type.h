00001 // <mutex> -*- C++ -*-
00002 
00003 // Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010
00004 // Free Software Foundation, Inc.
00005 //
00006 // This file is part of the GNU ISO C++ Library.  This library is free
00007 // software; you can redistribute it and/or modify it under the
00008 // terms of the GNU General Public License as published by the
00009 // Free Software Foundation; either version 3, or (at your option)
00010 // any later version.
00011 
00012 // This library is distributed in the hope that it will be useful,
00013 // but WITHOUT ANY WARRANTY; without even the implied warranty of
00014 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
00015 // GNU General Public License for more details.
00016 
00017 // Under Section 7 of GPL version 3, you are granted additional
00018 // permissions described in the GCC Runtime Library Exception, version
00019 // 3.1, as published by the Free Software Foundation.
00020 
00021 // You should have received a copy of the GNU General Public License and
00022 // a copy of the GCC Runtime Library Exception along with this program;
00023 // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
00024 // <http://www.gnu.org/licenses/>.
00025 
00026 /** @file mutex
00027  *  This is a Standard C++ Library header.
00028  */
00029 
00030 #ifndef _GLIBCXX_MUTEX
00031 #define _GLIBCXX_MUTEX 1
00032 
00033 #pragma GCC system_header
00034 
00035 #ifndef __GXX_EXPERIMENTAL_CXX0X__
00036 # include <bits/c++0x_warning.h>
00037 #else
00038 
00039 #include <tuple>
00040 #include <cstddef>
00041 #include <chrono>
00042 #include <exception>
00043 #include <type_traits>
00044 #include <functional>
00045 #include <system_error>
00046 #include <bits/functexcept.h>
00047 #include <bits/gthr.h>
00048 #include <bits/move.h> // for std::swap
00049 
00050 #if defined(_GLIBCXX_HAS_GTHREADS) && defined(_GLIBCXX_USE_C99_STDINT_TR1)
00051 
00052 namespace std
00053 {
00054   /**
00055    * @defgroup mutexes Mutexes
00056    * @ingroup concurrency
00057    *
00058    * Classes for mutex support.
00059    * @{
00060    */
00061 
00062   /// mutex
00063   class mutex
00064   {
00065     typedef __gthread_mutex_t           __native_type;
00066     __native_type  _M_mutex;
00067 
00068   public:
00069     typedef __native_type*          native_handle_type;
00070 
00071     mutex()
00072     {
00073       // XXX EAGAIN, ENOMEM, EPERM, EBUSY(may), EINVAL(may)
00074 #ifdef __GTHREAD_MUTEX_INIT
00075       __native_type __tmp = __GTHREAD_MUTEX_INIT;
00076       _M_mutex = __tmp;
00077 #else
00078       __GTHREAD_MUTEX_INIT_FUNCTION(&_M_mutex);
00079 #endif
00080     }
00081 
00082     mutex(const mutex&) = delete;
00083     mutex& operator=(const mutex&) = delete;
00084 
00085     void
00086     lock()
00087     {
00088       int __e = __gthread_mutex_lock(&_M_mutex);
00089 
00090       // EINVAL, EAGAIN, EBUSY, EINVAL, EDEADLK(may)
00091       if (__e)
00092     __throw_system_error(__e);
00093     }
00094 
00095     bool
00096     try_lock()
00097     {
00098       // XXX EINVAL, EAGAIN, EBUSY
00099       return !__gthread_mutex_trylock(&_M_mutex);
00100     }
00101 
00102     void
00103     unlock()
00104     {
00105       // XXX EINVAL, EAGAIN, EPERM
00106       __gthread_mutex_unlock(&_M_mutex);
00107     }
00108 
00109     native_handle_type
00110     native_handle()
00111     { return &_M_mutex; }
00112   };
00113 
00114   /// recursive_mutex
00115   class recursive_mutex
00116   {
00117     typedef __gthread_recursive_mutex_t     __native_type;
00118     __native_type  _M_mutex;
00119 
00120   public:
00121     typedef __native_type*          native_handle_type;
00122 
00123     recursive_mutex()
00124     {
00125       // XXX EAGAIN, ENOMEM, EPERM, EBUSY(may), EINVAL(may)
00126 #ifdef __GTHREAD_RECURSIVE_MUTEX_INIT
00127       __native_type __tmp = __GTHREAD_RECURSIVE_MUTEX_INIT;
00128       _M_mutex = __tmp;
00129 #else
00130       __GTHREAD_RECURSIVE_MUTEX_INIT_FUNCTION(&_M_mutex);
00131 #endif
00132     }
00133 
00134     recursive_mutex(const recursive_mutex&) = delete;
00135     recursive_mutex& operator=(const recursive_mutex&) = delete;
00136 
00137     void
00138     lock()
00139     {
00140       int __e = __gthread_recursive_mutex_lock(&_M_mutex);
00141 
00142       // EINVAL, EAGAIN, EBUSY, EINVAL, EDEADLK(may)
00143       if (__e)
00144     __throw_system_error(__e);
00145     }
00146 
00147     bool
00148     try_lock()
00149     {
00150       // XXX EINVAL, EAGAIN, EBUSY
00151       return !__gthread_recursive_mutex_trylock(&_M_mutex);
00152     }
00153 
00154     void
00155     unlock()
00156     {
00157       // XXX EINVAL, EAGAIN, EBUSY
00158       __gthread_recursive_mutex_unlock(&_M_mutex);
00159     }
00160 
00161     native_handle_type
00162     native_handle()
00163     { return &_M_mutex; }
00164   };
00165 
00166   /// timed_mutex
00167   class timed_mutex
00168   {
00169     typedef __gthread_mutex_t           __native_type;
00170 
00171 #ifdef _GLIBCXX_USE_CLOCK_MONOTONIC
00172     typedef chrono::monotonic_clock         __clock_t;
00173 #else
00174     typedef chrono::high_resolution_clock   __clock_t;
00175 #endif
00176 
00177     __native_type  _M_mutex;
00178 
00179   public:
00180     typedef __native_type*          native_handle_type;
00181 
00182     timed_mutex()
00183     {
00184 #ifdef __GTHREAD_MUTEX_INIT
00185       __native_type __tmp = __GTHREAD_MUTEX_INIT;
00186       _M_mutex = __tmp;
00187 #else
00188       __GTHREAD_MUTEX_INIT_FUNCTION(&_M_mutex);
00189 #endif
00190     }
00191 
00192     timed_mutex(const timed_mutex&) = delete;
00193     timed_mutex& operator=(const timed_mutex&) = delete;
00194 
00195     void
00196     lock()
00197     {
00198       int __e = __gthread_mutex_lock(&_M_mutex);
00199 
00200       // EINVAL, EAGAIN, EBUSY, EINVAL, EDEADLK(may)
00201       if (__e)
00202     __throw_system_error(__e);
00203     }
00204 
00205     bool
00206     try_lock()
00207     {
00208       // XXX EINVAL, EAGAIN, EBUSY
00209       return !__gthread_mutex_trylock(&_M_mutex);
00210     }
00211 
00212     template <class _Rep, class _Period>
00213       bool
00214       try_lock_for(const chrono::duration<_Rep, _Period>& __rtime)
00215       { return __try_lock_for_impl(__rtime); }
00216 
00217     template <class _Clock, class _Duration>
00218       bool
00219       try_lock_until(const chrono::time_point<_Clock, _Duration>& __atime)
00220       {
00221     chrono::time_point<_Clock, chrono::seconds> __s =
00222       chrono::time_point_cast<chrono::seconds>(__atime);
00223 
00224     chrono::nanoseconds __ns =
00225       chrono::duration_cast<chrono::nanoseconds>(__atime - __s);
00226 
00227     __gthread_time_t __ts = {
00228       static_cast<std::time_t>(__s.time_since_epoch().count()),
00229       static_cast<long>(__ns.count())
00230     };
00231 
00232     return !__gthread_mutex_timedlock(&_M_mutex, &__ts);
00233       }
00234 
00235     void
00236     unlock()
00237     {
00238       // XXX EINVAL, EAGAIN, EBUSY
00239       __gthread_mutex_unlock(&_M_mutex);
00240     }
00241 
00242     native_handle_type
00243     native_handle()
00244     { return &_M_mutex; }
00245 
00246   private:
00247     template<typename _Rep, typename _Period>
00248       typename enable_if<
00249     ratio_less_equal<__clock_t::period, _Period>::value, bool>::type
00250       __try_lock_for_impl(const chrono::duration<_Rep, _Period>& __rtime)
00251       {
00252     __clock_t::time_point __atime = __clock_t::now()
00253       + chrono::duration_cast<__clock_t::duration>(__rtime);
00254 
00255     return try_lock_until(__atime);
00256       }
00257 
00258     template <typename _Rep, typename _Period>
00259       typename enable_if<
00260     !ratio_less_equal<__clock_t::period, _Period>::value, bool>::type
00261       __try_lock_for_impl(const chrono::duration<_Rep, _Period>& __rtime)
00262       {
00263     __clock_t::time_point __atime = __clock_t::now()
00264       + ++chrono::duration_cast<__clock_t::duration>(__rtime);
00265 
00266     return try_lock_until(__atime);
00267       }
00268   };
00269 
00270   /// recursive_timed_mutex
00271   class recursive_timed_mutex
00272   {
00273     typedef __gthread_recursive_mutex_t     __native_type;
00274 
00275 #ifdef _GLIBCXX_USE_CLOCK_MONOTONIC
00276     typedef chrono::monotonic_clock         __clock_t;
00277 #else
00278     typedef chrono::high_resolution_clock   __clock_t;
00279 #endif
00280 
00281     __native_type  _M_mutex;
00282 
00283   public:
00284     typedef __native_type*          native_handle_type;
00285 
00286     recursive_timed_mutex()
00287     {
00288       // XXX EAGAIN, ENOMEM, EPERM, EBUSY(may), EINVAL(may)
00289 #ifdef __GTHREAD_RECURSIVE_MUTEX_INIT
00290       __native_type __tmp = __GTHREAD_RECURSIVE_MUTEX_INIT;
00291       _M_mutex = __tmp;
00292 #else
00293       __GTHREAD_RECURSIVE_MUTEX_INIT_FUNCTION(&_M_mutex);
00294 #endif
00295     }
00296 
00297     recursive_timed_mutex(const recursive_timed_mutex&) = delete;
00298     recursive_timed_mutex& operator=(const recursive_timed_mutex&) = delete;
00299 
00300     void
00301     lock()
00302     {
00303       int __e = __gthread_recursive_mutex_lock(&_M_mutex);
00304 
00305       // EINVAL, EAGAIN, EBUSY, EINVAL, EDEADLK(may)
00306       if (__e)
00307     __throw_system_error(__e);
00308     }
00309 
00310     bool
00311     try_lock()
00312     {
00313       // XXX EINVAL, EAGAIN, EBUSY
00314       return !__gthread_recursive_mutex_trylock(&_M_mutex);
00315     }
00316 
00317     template <class _Rep, class _Period>
00318       bool
00319       try_lock_for(const chrono::duration<_Rep, _Period>& __rtime)
00320       { return __try_lock_for_impl(__rtime); }
00321 
00322     template <class _Clock, class _Duration>
00323       bool
00324       try_lock_until(const chrono::time_point<_Clock, _Duration>& __atime)
00325       {
00326     chrono::time_point<_Clock, chrono::seconds>  __s =
00327       chrono::time_point_cast<chrono::seconds>(__atime);
00328 
00329     chrono::nanoseconds __ns =
00330       chrono::duration_cast<chrono::nanoseconds>(__atime - __s);
00331 
00332     __gthread_time_t __ts = {
00333       static_cast<std::time_t>(__s.time_since_epoch().count()),
00334       static_cast<long>(__ns.count())
00335     };
00336 
00337     return !__gthread_recursive_mutex_timedlock(&_M_mutex, &__ts);
00338       }
00339 
00340     void
00341     unlock()
00342     {
00343       // XXX EINVAL, EAGAIN, EBUSY
00344       __gthread_recursive_mutex_unlock(&_M_mutex);
00345     }
00346 
00347     native_handle_type
00348     native_handle()
00349     { return &_M_mutex; }
00350 
00351   private:
00352     template<typename _Rep, typename _Period>
00353       typename enable_if<
00354     ratio_less_equal<__clock_t::period, _Period>::value, bool>::type
00355       __try_lock_for_impl(const chrono::duration<_Rep, _Period>& __rtime)
00356       {
00357     __clock_t::time_point __atime = __clock_t::now()
00358       + chrono::duration_cast<__clock_t::duration>(__rtime);
00359 
00360     return try_lock_until(__atime);
00361       }
00362 
00363     template <typename _Rep, typename _Period>
00364       typename enable_if<
00365     !ratio_less_equal<__clock_t::period, _Period>::value, bool>::type
00366       __try_lock_for_impl(const chrono::duration<_Rep, _Period>& __rtime)
00367       {
00368     __clock_t::time_point __atime = __clock_t::now()
00369       + ++chrono::duration_cast<__clock_t::duration>(__rtime);
00370 
00371     return try_lock_until(__atime);
00372       }
00373   };
00374 
00375   /// Do not acquire ownership of the mutex.
00376   struct defer_lock_t { };
00377 
00378   /// Try to acquire ownership of the mutex without blocking.
00379   struct try_to_lock_t { };
00380 
00381   /// Assume the calling thread has already obtained mutex ownership
00382   /// and manage it.
00383   struct adopt_lock_t { };
00384 
00385   extern const defer_lock_t defer_lock;
00386   extern const try_to_lock_t    try_to_lock;
00387   extern const adopt_lock_t adopt_lock;
00388 
00389   /// @brief  Scoped lock idiom.
00390   // Acquire the mutex here with a constructor call, then release with
00391   // the destructor call in accordance with RAII style.
00392   template<typename _Mutex>
00393     class lock_guard
00394     {
00395     public:
00396       typedef _Mutex mutex_type;
00397 
00398       explicit lock_guard(mutex_type& __m) : _M_device(__m)
00399       { _M_device.lock(); }
00400 
00401       lock_guard(mutex_type& __m, adopt_lock_t) : _M_device(__m)
00402       { } // calling thread owns mutex
00403 
00404       ~lock_guard()
00405       { _M_device.unlock(); }
00406 
00407       lock_guard(const lock_guard&) = delete;
00408       lock_guard& operator=(const lock_guard&) = delete;
00409 
00410     private:
00411       mutex_type&  _M_device;
00412     };
00413 
00414   /// unique_lock
00415   template<typename _Mutex>
00416     class unique_lock
00417     {
00418     public:
00419       typedef _Mutex mutex_type;
00420 
00421       unique_lock()
00422       : _M_device(0), _M_owns(false)
00423       { }
00424 
00425       explicit unique_lock(mutex_type& __m)
00426       : _M_device(&__m), _M_owns(false)
00427       {
00428     lock();
00429     _M_owns = true;
00430       }
00431 
00432       unique_lock(mutex_type& __m, defer_lock_t)
00433       : _M_device(&__m), _M_owns(false)
00434       { }
00435 
00436       unique_lock(mutex_type& __m, try_to_lock_t)
00437       : _M_device(&__m), _M_owns(_M_device->try_lock())
00438       { }
00439 
00440       unique_lock(mutex_type& __m, adopt_lock_t)
00441       : _M_device(&__m), _M_owns(true)
00442       {
00443     // XXX calling thread owns mutex
00444       }
00445 
00446       template<typename _Clock, typename _Duration>
00447     unique_lock(mutex_type& __m,
00448             const chrono::time_point<_Clock, _Duration>& __atime)
00449     : _M_device(&__m), _M_owns(_M_device->try_lock_until(__atime))
00450     { }
00451 
00452       template<typename _Rep, typename _Period>
00453     unique_lock(mutex_type& __m,
00454             const chrono::duration<_Rep, _Period>& __rtime)
00455     : _M_device(&__m), _M_owns(_M_device->try_lock_for(__rtime))
00456     { }
00457 
00458       ~unique_lock()
00459       {
00460     if (_M_owns)
00461       unlock();
00462       }
00463 
00464       unique_lock(const unique_lock&) = delete;
00465       unique_lock& operator=(const unique_lock&) = delete;
00466 
00467       unique_lock(unique_lock&& __u)
00468       : _M_device(__u._M_device), _M_owns(__u._M_owns)
00469       {
00470     __u._M_device = 0;
00471     __u._M_owns = false;
00472       }
00473 
00474       unique_lock& operator=(unique_lock&& __u)
00475       {
00476     if(_M_owns)
00477       unlock();
00478 
00479     unique_lock(std::move(__u)).swap(*this);
00480 
00481     __u._M_device = 0;
00482     __u._M_owns = false;
00483 
00484     return *this;
00485       }
00486 
00487       void
00488       lock()
00489       {
00490     if (!_M_device)
00491       __throw_system_error(int(errc::operation_not_permitted));
00492     else if (_M_owns)
00493       __throw_system_error(int(errc::resource_deadlock_would_occur));
00494     else
00495       {
00496         _M_device->lock();
00497         _M_owns = true;
00498       }
00499       }
00500 
00501       bool
00502       try_lock()
00503       {
00504     if (!_M_device)
00505       __throw_system_error(int(errc::operation_not_permitted));
00506     else if (_M_owns)
00507       __throw_system_error(int(errc::resource_deadlock_would_occur));
00508     else
00509       {
00510         _M_owns = _M_device->try_lock();
00511         return _M_owns;
00512       }
00513       }
00514 
00515       template<typename _Clock, typename _Duration>
00516     bool
00517     try_lock_until(const chrono::time_point<_Clock, _Duration>& __atime)
00518     {
00519       if (!_M_device)
00520         __throw_system_error(int(errc::operation_not_permitted));
00521       else if (_M_owns)
00522         __throw_system_error(int(errc::resource_deadlock_would_occur));
00523       else
00524         {
00525           _M_owns = _M_device->try_lock_until(__atime);
00526           return _M_owns;
00527         }
00528     }
00529 
00530       template<typename _Rep, typename _Period>
00531     bool
00532     try_lock_for(const chrono::duration<_Rep, _Period>& __rtime)
00533     {
00534       if (!_M_device)
00535         __throw_system_error(int(errc::operation_not_permitted));
00536       else if (_M_owns)
00537         __throw_system_error(int(errc::resource_deadlock_would_occur));
00538       else
00539         {
00540           _M_owns = _M_device->try_lock_for(__rtime);
00541           return _M_owns;
00542         }
00543      }
00544 
00545       void
00546       unlock()
00547       {
00548     if (!_M_owns)
00549       __throw_system_error(int(errc::operation_not_permitted));
00550     else if (_M_device)
00551       {
00552         _M_device->unlock();
00553         _M_owns = false;
00554       }
00555       }
00556 
00557       void
00558       swap(unique_lock& __u)
00559       {
00560     std::swap(_M_device, __u._M_device);
00561     std::swap(_M_owns, __u._M_owns);
00562       }
00563 
00564       mutex_type*
00565       release()
00566       {
00567     mutex_type* __ret = _M_device;
00568     _M_device = 0;
00569     _M_owns = false;
00570     return __ret;
00571       }
00572 
00573       bool
00574       owns_lock() const
00575       { return _M_owns; }
00576 
00577       explicit operator bool() const
00578       { return owns_lock(); }
00579 
00580       mutex_type*
00581       mutex() const
00582       { return _M_device; }
00583 
00584     private:
00585       mutex_type*   _M_device;
00586       bool      _M_owns; // XXX use atomic_bool
00587     };
00588 
00589   template<typename _Mutex>
00590     inline void
00591     swap(unique_lock<_Mutex>& __x, unique_lock<_Mutex>& __y)
00592     { __x.swap(__y); }
00593 
00594   template<int _Idx>
00595     struct __unlock_impl
00596     {
00597       template<typename... _Lock>
00598     static void
00599     __do_unlock(tuple<_Lock&...>& __locks)
00600     {
00601       std::get<_Idx>(__locks).unlock();
00602       __unlock_impl<_Idx - 1>::__do_unlock(__locks);
00603     }
00604     };
00605 
00606   template<>
00607     struct __unlock_impl<-1>
00608     {
00609       template<typename... _Lock>
00610     static void
00611     __do_unlock(tuple<_Lock&...>&)
00612     { }
00613     };
00614 
00615   template<int _Idx, bool _Continue = true>
00616     struct __try_lock_impl
00617     {
00618       template<typename... _Lock>
00619     static int
00620     __do_try_lock(tuple<_Lock&...>& __locks)
00621     {
00622       if(std::get<_Idx>(__locks).try_lock())
00623         {
00624           return __try_lock_impl<_Idx + 1,
00625         _Idx + 2 < sizeof...(_Lock)>::__do_try_lock(__locks);
00626         }
00627       else
00628         {
00629           __unlock_impl<_Idx>::__do_unlock(__locks);
00630           return _Idx;
00631         }
00632     }
00633     };
00634 
00635   template<int _Idx>
00636     struct __try_lock_impl<_Idx, false>
00637     {
00638       template<typename... _Lock>
00639     static int
00640     __do_try_lock(tuple<_Lock&...>& __locks)
00641     {
00642       if(std::get<_Idx>(__locks).try_lock())
00643         return -1;
00644       else
00645         {
00646           __unlock_impl<_Idx>::__do_unlock(__locks);
00647           return _Idx;
00648         }
00649     }
00650     };
00651 
00652   /** @brief Generic try_lock.
00653    *  @param __l1 Meets Mutex requirements (try_lock() may throw).
00654    *  @param __l2 Meets Mutex requirements (try_lock() may throw).
00655    *  @param __l3 Meets Mutex requirements (try_lock() may throw).
00656    *  @return Returns -1 if all try_lock() calls return true. Otherwise returns
00657    *          a 0-based index corresponding to the argument that returned false.
00658    *  @post Either all arguments are locked, or none will be.
00659    *
00660    *  Sequentially calls try_lock() on each argument.
00661    */
00662   template<typename _Lock1, typename _Lock2, typename... _Lock3>
00663     int
00664     try_lock(_Lock1& __l1, _Lock2& __l2, _Lock3&... __l3)
00665     {
00666       tuple<_Lock1&, _Lock2&, _Lock3&...> __locks(__l1, __l2, __l3...);
00667       return __try_lock_impl<0>::__do_try_lock(__locks);
00668     }
00669 
00670   /// lock
00671   template<typename _L1, typename _L2, typename ..._L3>
00672     void
00673     lock(_L1&, _L2&, _L3&...);
00674 
00675   /// once_flag
00676   struct once_flag
00677   {
00678   private:
00679     typedef __gthread_once_t __native_type;
00680     __native_type  _M_once;
00681 
00682   public:
00683     once_flag()
00684     {
00685       __native_type __tmp = __GTHREAD_ONCE_INIT;
00686       _M_once = __tmp;
00687     }
00688 
00689     once_flag(const once_flag&) = delete;
00690     once_flag& operator=(const once_flag&) = delete;
00691 
00692     template<typename _Callable, typename... _Args>
00693       friend void
00694       call_once(once_flag& __once, _Callable __f, _Args&&... __args);
00695   };
00696 
00697 #ifdef _GLIBCXX_HAVE_TLS
00698   extern __thread void* __once_callable;
00699   extern __thread void (*__once_call)();
00700 
00701   template<typename _Callable>
00702     inline void
00703     __once_call_impl()
00704     {
00705       (*(_Callable*)__once_callable)();
00706     }
00707 #else
00708   extern function<void()> __once_functor;
00709 
00710   extern void
00711   __set_once_functor_lock_ptr(unique_lock<mutex>*);
00712 
00713   extern mutex&
00714   __get_once_mutex();
00715 #endif
00716 
00717   extern "C" void __once_proxy();
00718 
00719   /// call_once
00720   template<typename _Callable, typename... _Args>
00721     void
00722     call_once(once_flag& __once, _Callable __f, _Args&&... __args)
00723     {
00724 #ifdef _GLIBCXX_HAVE_TLS
00725       auto __bound_functor = std::bind<void>(__f, __args...);
00726       __once_callable = &__bound_functor;
00727       __once_call = &__once_call_impl<decltype(__bound_functor)>;
00728 #else
00729       unique_lock<mutex> __functor_lock(__get_once_mutex());
00730       __once_functor = std::bind<void>(__f, __args...);
00731       __set_once_functor_lock_ptr(&__functor_lock);
00732 #endif
00733 
00734       int __e = __gthread_once(&(__once._M_once), &__once_proxy);
00735 
00736 #ifndef _GLIBCXX_HAVE_TLS
00737       if (__functor_lock)
00738         __set_once_functor_lock_ptr(0);
00739 #endif
00740 
00741       if (__e)
00742     __throw_system_error(__e);
00743     }
00744 
00745   // @} group mutexes
00746 }
00747 
00748 #endif // _GLIBCXX_HAS_GTHREADS && _GLIBCXX_USE_C99_STDINT_TR1
00749 
00750 #endif // __GXX_EXPERIMENTAL_CXX0X__
00751 
00752 #endif // _GLIBCXX_MUTEX
