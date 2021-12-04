import os
from shutil import copyfile

def GetArgs(is_debug):
  args = {
    "is_component_build": True,
    "skia_use_system_expat": False,
    "skia_use_system_libjpeg_turbo": False,
    "skia_use_system_libpng": False,
    "skia_use_system_libwebp": False,
    "skia_use_system_zlib": False,
    "skia_use_system_icu": False,
    "skia_use_system_harfbuzz": False,
    "skia_use_gl": True,
    "is_debug": is_debug,
    "is_official_build": not is_debug
  }
  return " ".join(map(lambda x : "{}={}".format(x[0], str(x[1]).lower()) , args.items()))

def CopyDlls(skia_root, is_debug):
  root_src = "{}/out/{}".format(skia_root, "Debug" if is_debug else "Release")
  root_dst = "{}/../bin/{}".format(skia_root, "Debug" if is_debug else "Release")
  files = [ "skia.dll", "skia.dll.lib" ]
  for file in files:
    copyfile("{}/{}".format(root_src, file), "{}/{}".format(root_dst, file))

def main():
  root = os.getcwd()
  skia_root = "{}/external/skia/skia".format(root)
  bin_root = "{}/build/bin".format(root)

  # update dependencies
  os.system("python {}/tools/git-sync-deps".format(skia_root))

  for type in ["Debug", "Release"]:
    is_debug = (type == "Debug")
    os.system("cd {} && {}/gn gen out/{} --args=\"{}\"".format(skia_root, bin_root, type, GetArgs(is_debug)))
    os.system("cd {} && {}/ninja -C out/{}".format(skia_root, bin_root, type))
    CopyDlls(skia_root, is_debug)

if __name__ == "__main__":
  main()