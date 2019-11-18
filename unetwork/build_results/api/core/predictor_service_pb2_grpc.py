# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
import grpc

from api.core import predictor_service_pb2 as api_dot_core_dot_predictor__service__pb2


class PredictorServiceStub(object):
  """Main class for predictor services through platform.
  """

  def __init__(self, channel):
    """Constructor.

    Args:
      channel: A grpc.Channel.
    """
    self.Predict = channel.unary_unary(
        '/api.PredictorService/Predict',
        request_serializer=api_dot_core_dot_predictor__service__pb2.PredictRequest.SerializeToString,
        response_deserializer=api_dot_core_dot_predictor__service__pb2.PredictReponse.FromString,
        )


class PredictorServiceServicer(object):
  """Main class for predictor services through platform.
  """

  def Predict(self, request, context):
    """Predicts actions
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')


def add_PredictorServiceServicer_to_server(servicer, server):
  rpc_method_handlers = {
      'Predict': grpc.unary_unary_rpc_method_handler(
          servicer.Predict,
          request_deserializer=api_dot_core_dot_predictor__service__pb2.PredictRequest.FromString,
          response_serializer=api_dot_core_dot_predictor__service__pb2.PredictReponse.SerializeToString,
      ),
  }
  generic_handler = grpc.method_handlers_generic_handler(
      'api.PredictorService', rpc_method_handlers)
  server.add_generic_rpc_handlers((generic_handler,))
