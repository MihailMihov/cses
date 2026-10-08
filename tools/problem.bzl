"""One standalone solution and one test per samples/*.in + *.out pair."""

load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_shell//shell:sh_test.bzl", "sh_test")

def _cses_problem_impl(name, visibility, srcs, sample_inputs, sample_outputs):
    cc_binary(
        name = name,
        srcs = srcs,
        visibility = visibility,
    )

    for input_file in sample_inputs:
        output_file = input_file.same_package_label(input_file.name[:-3] + ".out")
        if output_file not in sample_outputs:
            fail("Missing expected output: %s" % output_file)
        sh_test(
            name = name + "_" + input_file.name[len("samples/"):-3] + "_test",
            srcs = ["//tools:check.sh"],
            args = [
                "$(rootpath :%s)" % name,
                "$(rootpath %s)" % input_file,
                "$(rootpath %s)" % output_file,
            ],
            data = [":" + name, input_file, output_file],
            visibility = visibility,
            size = "small",
        )
    for output_file in sample_outputs:
        if output_file.same_package_label(output_file.name[:-4] + ".in") not in sample_inputs:
            fail("Missing input for: %s" % output_file)

cses_problem = macro(
    doc = "Create a solution binary named name and a name_<sample>_test per sample pair.",
    attrs = {
        "srcs": attr.label_list(
            mandatory = True,
            allow_files = True,
            doc = "C++ solution source files.",
        ),
        "sample_inputs": attr.label_list(
            allow_files = [".in"],
            configurable = False,
            doc = "Input files from glob([\"samples/*.in\"]) in the calling BUILD file.",
        ),
        "sample_outputs": attr.label_list(
            allow_files = [".out"],
            configurable = False,
            doc = "Expected outputs from glob([\"samples/*.out\"]) in the calling BUILD file.",
        ),
    },
    implementation = _cses_problem_impl,
)
