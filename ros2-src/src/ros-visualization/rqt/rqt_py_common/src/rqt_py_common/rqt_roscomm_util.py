# Software License Agreement (BSD License)
#
# Copyright (c) 2012, Willow Garage, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#    * Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#
#    * Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#
#    * Neither the name of the copyright holder nor the names of its
#      contributors may be used to endorse or promote products derived from
#      this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Author: Isaac Saito

import os

from ament_index_python import get_resources

from rclpy import logging


class RqtRoscommUtil(object):
    _logger = logging.get_logger('RqtRoscommUtil')

    @staticmethod
    def load_parameters(config, caller_id):
        """
        TODO(mlautman) Load parameters from node graph.

        Load parameters onto the parameter server.

        Copied from ROSLaunchRunner.

        @type config: roslaunch.config.ROSLaunchConfig
        @raise RLException:
        """
        # XMLRPC proxy for communicating with master, 'xmlrpclib.ServerProxy'
        # param_server = config.master.get()

        # param = None
        # try:
        #     # multi-call style xmlrpc
        #     # According to API doc, get_multi() returns
        #     # multicall XMLRPC proxy for communicating with master,
        #     # "xmlrpclib.MultiCall"
        #     param_server_multi = config.master.get_multi()

        #     # clear specified parameter namespaces
        #     # 2468 unify clear params to prevent error
        #     for param in roslaunch.launch._unify_clear_params(config.clear_params):
        #         if param_server.hasParam(caller_id, param)[2]:
        #             param_server_multi.deleteParam(caller_id, param)
        #     r = param_server_multi()
        #     for code, msg, _ in r:
        #         if code != 1:
        #             raise RLException("Failed to clear parameter {}: ".format(msg))
        # except RLException:
        #     raise
        # except Exception as e:
        #     RqtRoscommUtil._logger.error(
        #         "load_parameters: unable to set params (last param was [{}]): {}".format(
        #             param, e))
        #     raise  # re-raise as this is fatal

        # try:
        #     # multi-call objects are not reusable
        #     param_server_multi = config.master.get_multi()
        #     for param in config.params.values():
        #         # suppressing this as it causes too much spam
        #         # printlog("setting parameter [%s]"%param.key)
        #         param_server_multi.setParam(caller_id, param.key, param.value)
        #     r = param_server_multi()
        #     for code, msg, _ in r:
        #         if code != 1:
        #             raise RLException("Failed to set parameter: %s" % (msg))
        # except RLException:
        #     raise
        # except Exception as e:
        #     print(
        #         "load_parameters: unable to set params (last param was [%s]): %s" % (param, e))
        #     raise  # re-raise as this is fatal
        # RqtRoscommUtil._logger.debug("... load_parameters complete")
        RqtRoscommUtil._logger.error('load_parameters: not yet implemented in ROS2))')
        pass

    @staticmethod
    def iterate_packages(subdir):
        """
        Iterate packages that contain the given subdir.

        This method is generalizing rosmsg.iterate_packages.

        @param subdir: eg. 'launch', 'msg', 'srv', 'action'
        @type subdir: str
        @raise ValueError:
        """
        if subdir is None or subdir == '':
            raise ValueError('Invalid package subdir = {}'.format(subdir))

        packages_map = get_resources('packages')
        for package_name, package_path in packages_map.items():
            package_path = os.path.join(package_path, 'share', package_name, subdir)
            RqtRoscommUtil._logger.debug(
                'package:\t{} dir:\t{}'.format(package_name, package_path))
            if os.path.isdir(package_path):
                yield package_name, package_path

    @staticmethod
    def list_files(package, subdir, file_extension='.launch'):
        """
        List files contained in the specified package.

        Note: Mlautman 11/2/2018
              This method is deprecated in ROS2
              This functionality does not fit the ROS2 design paradigm
              of explicitly exporting resources to a shared location.

        #TODO: Come up with better name of the method.

        Taken from rosmsg.

        @param package: package name, ``str``
        @param file_extension: Defaults to '.launch', ``str``
        :returns: list of msgs/srv in package, ``[str]``
        """
        RqtRoscommUtil._logger.error('list_files: not implemented in ROS2))')
        pass

    @staticmethod
    def _list_types(path, ext):
        """
        List all messages in the specified package.

        Taken from rosmsg.

        :param package str: name of package to search
        :param include_depends bool: if True, will also list messages in
                                     package dependencies.
        :returns [str]: message type names
        """
        types = RqtRoscommUtil._list_resources(path,
                                               RqtRoscommUtil._msg_filter(ext))

        result = list(types)
        # result = [x[:-len(ext)] for x in types]  # Remove extension

        result.sort()
        return result

    @staticmethod
    def _list_resources(path, rfilter=os.path.isfile):
        """
        List resources in a package directory within a particular.

        Taken from rosmsg._list_resources.

        subdirectory. This is useful for listing messages, services, etc...
        :param rfilter: resource filter function that returns true if filename
                        is the desired resource type, ``fn(filename)->bool``
        """
        resources = []
        if os.path.isdir(path):
            resources = [f for f
                         in os.listdir(path) if rfilter(os.path.join(path, f))]
        else:
            resources = []
        return resources

    @staticmethod
    def _msg_filter(ext):
        """Taken from rosmsg._msg_filter."""
        def mfilter(f):
            """
            Predicate for filtering directory list. matches message files.

            :param f: filename, ``str``
            """
            return os.path.isfile(f) and f.endswith(ext)
        return mfilter
