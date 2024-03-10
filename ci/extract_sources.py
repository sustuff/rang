#!/usr/bin/python

import argparse
import glob
import json

def extract_sources(build_dir: str, target_name: str):
    API_REPLY = f"{build_dir}/.cmake/api/v1/reply"

    index_path = glob.glob(f"{API_REPLY}/index-*.json")
    with open(index_path[0], "r") as index_file:
        index = json.load(index_file)

    codemodel_path = index["reply"]["codemodel-v2"]["jsonFile"]
    with open(f"{API_REPLY}/{codemodel_path}", "r") as codemodel_file:
        codemodel = json.load(codemodel_file)

    target_paths = []
    for cfg in codemodel["configurations"]:
        for target in cfg["targets"]:
            if target["name"] == target_name:
                target_paths.append(target["jsonFile"])

    sources = []
    for target_path in target_paths:
        with open(f"{API_REPLY}/{target_path}", "r") as target_file:
            target = json.load(target_file)
            sources += target["sources"]

    return sources


def get_notgenerated_sources(sources) -> [str]:
    result = set()
    for source in sources:
        if source.get("isGenerated", False) or source.get("backtrace", 0) == 0:
            continue
        result.add(source["path"])
    return list(result)


parser = argparse.ArgumentParser(prog="extract_sources",
                                 description="Extracts CMake source files from API")
parser.add_argument("target_name")
parser.add_argument("-b", "--build-dir", dest="build_dir", default="build")
args = parser.parse_args()

sources = extract_sources(args.build_dir, args.target_name)
print(*get_notgenerated_sources(sources), sep='\n')
