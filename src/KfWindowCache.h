/*********************************************************************************
 *   Copyright (C) 2006-2013 by Sebastian Gniazdowski                            *
 *   All Rights reserved.                                                        *
 *                                                                               *
 *   Redistribution and use in source and binary forms, with or without          *
 *   modification, are permitted provided that the following conditions          *
 *   are met:                                                                    *
 *   1. Redistributions of source code must retain the above copyright           *
 *      notice, this list of conditions and the following disclaimer.            *
 *   2. Redistributions in binary form must reproduce the above copyright        *
 *      notice, this list of conditions and the following disclaimer in the      *
 *      documentation and/or other materials provided with the distribution.     *
 *   3. Neither the name of the Keyfrog nor the names of its contributors        *
 *      may be used to endorse or promote products derived from this software    *
 *      without specific prior written permission.                               *
 *                                                                               *
 *   THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND     *
 *   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       *
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  *
 *   ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE    *
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL  *
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS     *
 *   OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)       *
 *   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT  *
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY   *
 *   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF      *
 *   SUCH DAMAGE.                                                                *
 *********************************************************************************/

#ifndef KEYFROGKFWINDOWCACHE_H
#define KEYFROGKFWINDOWCACHE_H

#include "KfWindow.h"
#include <map>
#include <sys/types.h>
#include <X11/Xlib.h>

namespace keyfrog {

    typedef std::map<Window, KfWindow> X11WindowInfoCache;
    typedef std::map<Window, KfWindow>::iterator X11WindowInfoCache_it;

    /**
     * @author Sebastian Gniazdowski
     */
    class KfWindowCache {
        Display *m_display;
        /// Each window has it's information structure
        X11WindowInfoCache m_cache;
        /// Cache entryused last time - to avoid searching in map
        X11WindowInfoCache_it m_currentCacheEntry;

        bool getWindowParent(Window & winId, Window & root);

        public:
        KfWindowCache();

        KfWindowCache(Display *display);

        ~KfWindowCache();

        bool findAndUseWindow(Window window);

        /**
         * Returns current window ID, or 0 (FIXME)
         */
        Window currentWindow() {
            if( m_cache.end() == m_currentCacheEntry )
                return (Window)0;
            return m_currentCacheEntry->first;
        }

        const std::string & fetchClassName();

        pid_t fetchClientPid();

        std::string resolveClassName(Window winId);

        pid_t resolveClientPid(Window winId);

        void invalidateEntry();

        void setDisplay(Display * display) {
            // FIXME
            m_display = display;
        }
    };
}
#endif