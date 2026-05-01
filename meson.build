project(
  'ascii_clock',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : ['warning_level=3'],
)

dependencies = [
]

sources = [
  'ascii_clock.c',
  'src/font.c',
]

exe = executable(
  'ascii_clock',
  sources,
  dependencies : dependencies,
  install : true,
)

test('basic', exe)
