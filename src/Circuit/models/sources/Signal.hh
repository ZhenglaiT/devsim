/***
DEVSIM
Copyright 2013 DEVSIM LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***/

#ifndef SIGNAL_HH
#define SIGNAL_HH

#include <memory>

class Signal;
typedef std::shared_ptr<Signal> SignalPtr;

class Signal {
   public:
      enum class SignalType {DCONLY, PULSE};
      virtual ~Signal() {};
      virtual double NextBreakPoint(double)=0;
      virtual double CalcVoltage(double)=0;
      double getVoltage() {return _volt;}
      void   setVoltage(double v) {_volt = v;}
   protected:
      Signal (SignalType);
      double _volt = 0.0;
   private:
      Signal();
      Signal(const Signal &);
//      Signal operator=(const Signal &);

      SignalType _type;
};

class DCOnly : public Signal {
   public:
      explicit DCOnly (double);
      double NextBreakPoint(double);
      // time based
      double CalcVoltage(double);
   protected:
   private:
      DCOnly();
      DCOnly(const DCOnly &);
      DCOnly operator=(const DCOnly &);
};

class Pulse : public Signal {
   public:
      double NextBreakPoint(double);
      double CalcVoltage(double);
      Pulse(double, double, double, double, double, double, double);
   protected:
   private:
      Pulse();
      Pulse(const Pulse &);
      Pulse operator=(const Pulse &);

      double _v1; // initial voltage
      double _v2; // pulsed voltage
      double _td; // delay time
      double _tr; // rise time
      double _tf; // fall time
      double _pw; // pulse width
      double _per; // pulse width
};

#endif
