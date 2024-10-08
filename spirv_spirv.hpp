/*
 * Copyright 2024 Kitsunebi Games
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * At your option, you may choose to accept this material under either:
 *  1. The Apache License, Version 2.0, found at <http://www.apache.org/licenses/LICENSE-2.0>, or
 *  2. The MIT License, found at <http://opensource.org/licenses/MIT>.
 */

#ifndef SPIRV_CROSS_SPIRV_HPP
#define SPIRV_CROSS_SPIRV_HPP

#include "spirv_glsl.hpp"
#include <map>
#include <set>
#include <stddef.h>
#include <vector>

namespace SPIRV_CROSS_NAMESPACE
{
class CompilerSPIRV : public CompilerGLSL
{
public:
	explicit CompilerSPIRV(std::vector<uint32_t> spirv);
	CompilerSPIRV(const uint32_t *ir, size_t word_count);
	explicit CompilerSPIRV(const ParsedIR &ir);
	explicit CompilerSPIRV(ParsedIR &&ir);

	std::string compile() override;

private:
	std::vector<uint32_t> buffer;

	// The different stages of emitting SPIRV.
	void emit_header();
	void emit_capabilities();
	void emit_extensions();
	void emit_ext_inst_imports();
	void emit_exec_info();
	void emit_annotations();
	void emit_types();
	void emit_function_defs();
	void emit_functions();

	// Helper functions
	void emit_opcode(spv::Op opcode, uint32_t arglength = 0);
	void emit_id(uint32_t id);
	void emit_string(std::vector<uint32_t> str);
	std::vector<uint32_t> get_spirv_string(std::string str);

	// Decoration helpers
	std::vector<spv::Decoration> get_decoration_list(Meta::Decoration decoration);
	void emit_decorations(ID id, Meta::Decoration decoration);
	void emit_decorations_member(uint32_t offset, ID id, Meta::Decoration decoration);
	void emit_decorations_operand(spv::Decoration decoration, Meta::Decoration meta);
	bool has_decorations(Meta::Decoration decoration);
};
} // namespace SPIRV_CROSS_NAMESPACE

#endif