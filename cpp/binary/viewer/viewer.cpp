/*
 * Copyright (c) 2022, Yung-Yu Chen <yyc@solvcon.net>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the copyright holder nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <modmesh/python/python.hpp> // Must be the first include.
#include <modmesh/python/wrapper/modmesh/modmesh.hpp>
#include <modmesh/python/wrapper/onedim/onedim.hpp>
#include <modmesh/python/wrapper/spacetime/spacetime.hpp>
#include <modmesh/modmesh.hpp>
#include <modmesh/view/view.hpp>
#include <modmesh/view/wrap_view.hpp>
#ifdef MODMESH_METAL
#include <modmesh/device/metal/metal.hpp>
#endif // MODMESH_METAL

PYBIND11_EMBEDDED_MODULE(_modmesh, mod) // NOLINT
{
    modmesh::python::initialize_modmesh(mod);
    pybind11::module_ spacetime_mod = mod.def_submodule("spacetime", "spacetime");
    modmesh::python::initialize_spacetime(spacetime_mod);
    pybind11::module_ onedim_mod = mod.def_submodule("onedim", "onedim");
    modmesh::python::initialize_onedim(onedim_mod);
}

PYBIND11_EMBEDDED_MODULE(_modmesh_view, mod) // NOLINT
{
    modmesh::python::initialize_view(mod);
}

int main(int argc, char ** argv)
{
    // Set up Python interpreter.
    modmesh::python::Interpreter::instance().initialize();

#ifdef MODMESH_METAL
    modmesh::device::MetalManager::instance();
#endif // MODMESH_METAL

    modmesh::RApplication app(argc, argv);
    app.main()->resize(1000, 600);
    return app.exec();
}

// vim: set ff=unix fenc=utf8 et sw=4 ts=4 sts=4: