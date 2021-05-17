#include "sample.pb.h"
#include "serdescpp-protobuf.hpp"
#include "serdescpp.h"
#include "serdescpp_int.h"

#include <gtest/gtest.h>
#include <librdkafka/rdkafkacpp.h>

using namespace testing;

class MyDeliveryReportCb : public RdKafka::DeliveryReportCb
{
  public:
    void dr_cb(RdKafka::Message &msg)
    {
        switch (msg.err()) {
            case RdKafka::ERR_NO_ERROR:
                std::cerr << "% Message produced (offset " << msg.offset()
                          << ")" << std::endl;
                break;

            default:
                std::cerr << "% Message delivery failed: " << msg.errstr()
                          << std::endl;
        }
    }
};

TEST(LibSerdes, KafkaProtoBufSchemaProducer)
{
    using namespace Serdes;

    std::string errstr;
    std::string schemaName{"schema_proto_test_1"};
    std::string kafkaTopic{"biss_ndeath"};
    int partition = 0;

    Serdes::Conf *sconf = Serdes::Conf::create();
    ASSERT_EQ(
      sconf->set("schema.registry.url",
                 "https://NHRRCX3T4YVCEBPE:7C6/6WU/"
                 "6ApFU245VpgXgFqJGnWN5ZQsPCzN36ina3abBj0y/"
                 "RbrijC+eXF9L0B3@psrc-mvkrw.europe-west3.gcp.confluent.cloud",
                 errstr),
      SERDES_ERR_OK)
      << "Failed to set serdes url conf";

    ASSERT_EQ(sconf->set("serializer.framing", "cp1", errstr), SERDES_ERR_OK)
      << "Failed to set serdes url conf";

    RdKafka::Conf *kconf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);

    /* Create rdkafka default topic configuration object.
     * Configuration passed through -X kafka.topic.prop=val will be set .. */
    RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

    Serdes::Protobuf *serdes = Serdes::Protobuf::create(sconf, errstr);

    Serdes::Schema *schema = Serdes::Schema::get(serdes, schemaName, errstr);

    kconf->set("metadata.broker.list",
               "pkc-lzvrd.us-west4.gcp.confluent.cloud:9092", errstr);
    kconf->set("security.protocol", "sasl_ssl", errstr);
    kconf->set("sasl.mechanisms", "PLAIN", errstr);
    kconf->set("sasl.username", "IHPLOMYWAQ44MHDC", errstr);
    kconf->set(
      "sasl.password",
      "ZuboFXH96/oWLrqfUoA85ybyOGm1jozB+P1mODROdlyN6CLVuPdBO5dNrK/LG+/O",
      errstr);
    kconf->set("ssl.ca.location", "/etc/ssl/certs", errstr);
    kconf->set("client.id", "kafka_producer", errstr);

    /* Set up a delivery report callback to track delivery status on a
     * per message basis */
    MyDeliveryReportCb dr_cb;
    ASSERT_EQ(kconf->set("dr_cb", &dr_cb, errstr), RdKafka::Conf::CONF_OK);

    /* Create Kafka producer */
    RdKafka::Producer *producer = RdKafka::Producer::create(kconf, errstr);
    ASSERT_TRUE(producer != nullptr);

    /* Create topic object */
    RdKafka::Topic *ktopic =
      RdKafka::Topic::create(producer, kafkaTopic, tconf, errstr);
    ASSERT_TRUE(producer != nullptr);

    com::mycorp::mynamespace::SampleRecord sampleRecord;
    sampleRecord.set_my_field1(1);
    sampleRecord.set_my_field2(2);

    std::string serializedData;
    ASSERT_TRUE(sampleRecord.SerializeToString(&serializedData));

    std::vector<char> out;
    ASSERT_NE(serdes->serialize(schema, serializedData, out, errstr), -1);

    /* Produce to Kafka */
    ASSERT_EQ(producer->produce(ktopic, partition, &out, NULL, NULL),
              RdKafka::ERR_NO_ERROR);

    /* Wait for all messages to be delivered */
    while (producer->outq_len() > 0)
        producer->poll(100);

    delete producer;
    delete serdes;

    ASSERT_TRUE(true);
}

TEST(LibSerdes, KafkaProtoBufSchemaConsumer)
{
    using namespace Serdes;

    std::string errstr;
    std::string schemaName{"schema_proto_test_1"};
    std::string kafkaTopic{"biss_ndeath"};
    int partition = 0;

    Serdes::Conf *sconf = Serdes::Conf::create();
    ASSERT_EQ(
      sconf->set("schema.registry.url",
                 "https://NHRRCX3T4YVCEBPE:7C6/6WU/"
                 "6ApFU245VpgXgFqJGnWN5ZQsPCzN36ina3abBj0y/"
                 "RbrijC+eXF9L0B3@psrc-mvkrw.europe-west3.gcp.confluent.cloud",
                 errstr),
      SERDES_ERR_OK)
      << "Failed to set serdes url conf";

    ASSERT_EQ(sconf->set("serializer.framing", "cp1", errstr), SERDES_ERR_OK)
      << "Failed to set serdes url conf";

    RdKafka::Conf *kconf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);

    /* Create rdkafka default topic configuration object.
     * Configuration passed through -X kafka.topic.prop=val will be set .. */
    RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

    Serdes::Protobuf *serdes = Serdes::Protobuf::create(sconf, errstr);

    Serdes::Schema *schema = Serdes::Schema::get(serdes, schemaName, errstr);

    kconf->set("metadata.broker.list",
               "pkc-lzvrd.us-west4.gcp.confluent.cloud:9092", errstr);
    kconf->set("security.protocol", "sasl_ssl", errstr);
    kconf->set("sasl.mechanisms", "PLAIN", errstr);
    kconf->set("sasl.username", "IHPLOMYWAQ44MHDC", errstr);
    kconf->set(
      "sasl.password",
      "ZuboFXH96/oWLrqfUoA85ybyOGm1jozB+P1mODROdlyN6CLVuPdBO5dNrK/LG+/O",
      errstr);
    kconf->set("ssl.ca.location", "/etc/ssl/certs", errstr);
    kconf->set("client.id", "kafka_consumer", errstr);
    kconf->set("group.id", "kafka_example_consumer", errstr);
    kconf->set("debug", "consumer", errstr);
    kconf->set("enable.partition.eof", "false", errstr);
    kconf->set("enable.auto.commit", "false", errstr);

    /* Create Kafka consumer */
    RdKafka::KafkaConsumer *consumer =
      RdKafka::KafkaConsumer::create(kconf, errstr);
    ASSERT_TRUE(consumer != nullptr);

    ASSERT_EQ(consumer->subscribe({kafkaTopic}), RdKafka::ERR_NO_ERROR);

    RdKafka::Message *msg = consumer->consume(5000);

    ASSERT_EQ(msg->err(), RdKafka::ERR_NO_ERROR);

    /*std::string serializedData;
    ASSERT_NE(serdes->deserialize(&schema, serializedData, msg->payload(),
                                  msg->len(), errstr),
              -1);

    com::mycorp::mynamespace::SampleRecord sampleRecord;
    ASSERT_TRUE(sampleRecord.ParseFromString(serializedData));

    consumer->close();

    delete consumer;
    delete serdes;

    ASSERT_TRUE(true);
    */
}
