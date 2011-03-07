/*
  Copyright (c) 2011, The Mineserver Project
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the The Mineserver Project nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//
// Mineserver logger.cpp
//

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include "mineserver.h"
#include "tools.h"
#include "plugin.h"

#include "logger.h"
#include "logtype.h"

void Logger::log(const std::string& msg, const std::string& file, int line)
{
  std::ostringstream str;
  size_t pos;

  pos = file.rfind(PATH_SEPARATOR);
  if (pos != std::string::npos)
  {
    str << file.substr(pos + 1, file.length());
  }
  str << ":";
  str << (int)line;

  log(LogType::LOG_INFO, str.str(), msg);
}

void Logger::log(LogType::LogType type, const std::string& source, const std::string& message)
{
  (static_cast<Hook3<bool, int, const char*, const char*>*>(Mineserver::get()->plugin()->getHook("LogPost")))->doAll((int)type, source.c_str(), message.c_str());
}


