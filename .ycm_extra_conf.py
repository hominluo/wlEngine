import os
workingDirectory = os.path.dirname(os.path.abspath(__file__))

FLAGS = [
        '-x',
        'c++',
        '-std=c++14',
        '-Wall',
        '-Wextra',
        '-Werror',
        '-Wno-deprecated',
        '-I', workingDirectory + '/third_party/SDL2/include',
        '-I', workingDirectory + '/third_party/glm/include',
        '-I', workingDirectory + '/third_party/Box2D/include',
        '-I', workingDirectory + '/third_party/json/include'
        ]

def Settings( **kwargs ):
  return {
          'flags': FLAGS,
  }
