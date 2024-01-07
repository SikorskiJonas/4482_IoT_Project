/******************************************************************************
* File Name:   mqtt_client_config.h
*
* Description: This file contains all the configuration macros used by the
*              MQTT client in this example.
*
* Related Document: See README.md
*
*
*******************************************************************************
* Copyright 2020-2023, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#ifndef MQTT_CLIENT_CONFIG_H_
#define MQTT_CLIENT_CONFIG_H_

#include "cy_mqtt_api.h"

/*******************************************************************************
* Macros
********************************************************************************/

/***************** MQTT CLIENT CONNECTION CONFIGURATION MACROS *****************/
/* MQTT Broker/Server address and port used for the MQTT connection. */
#define MQTT_BROKER_ADDRESS               "broker.hivemq.com"
#define MQTT_PORT                         1883

/* Set this macro to 1 if a secure (TLS) connection to the MQTT Broker is  
 * required to be established, else 0.
 */
#define MQTT_SECURE_CONNECTION            ( 0 )

/* Configure the user credentials to be sent as part of MQTT CONNECT packet */
#define MQTT_USERNAME                     "xxxxxxxx"
#define MQTT_PASSWORD                     "xxxxxxxx"


/********************* MQTT MESSAGE CONFIGURATION MACROS **********************/
/* The MQTT topics to be used by the publisher and subscriber. */
#define MQTT_PUB_TOPIC                    "jonas_UHasselt_IoT_node2"
#define MQTT_SUB_TOPIC                    "jonas_UHasselt_IoT_py"

/* Set the QoS that is associated with the MQTT publish, and subscribe messages.
 * Valid choices are 0, 1, and 2. Other values should not be used in this macro.
 */
#define MQTT_MESSAGES_QOS                 ( 1 )

/* Configuration for the 'Last Will and Testament (LWT)'. It is an MQTT message 
 * that will be published by the MQTT broker if the MQTT connection is 
 * unexpectedly closed. This configuration is sent to the MQTT broker during 
 * MQTT connect operation and the MQTT broker will publish the Will message on 
 * the Will topic when it recognizes an unexpected disconnection from the client.
 * 
 * If you want to use the last will message, set this macro to 1 and configure
 * the topic and will message, else 0.
 */
#define ENABLE_LWT_MESSAGE                ( 0 )
#if ENABLE_LWT_MESSAGE
    #define MQTT_WILL_TOPIC_NAME          MQTT_PUB_TOPIC "/will"
    #define MQTT_WILL_MESSAGE             ("MQTT client unexpectedly disconnected!")
#endif

/* MQTT messages which are published on the MQTT_PUB_TOPIC that controls the
 * device (user LED in this example) state in this code example.
 */
#define MQTT_DEVICE_ON_MESSAGE            "TURN ON"
#define MQTT_DEVICE_OFF_MESSAGE           "TURN OFF"


/******************* OTHER MQTT CLIENT CONFIGURATION MACROS *******************/
/* A unique client identifier to be used for every MQTT connection. */
#define MQTT_CLIENT_IDENTIFIER            "psoc6-mqtt-client"

/* The timeout in milliseconds for MQTT operations in this example. */
#define MQTT_TIMEOUT_MS                   ( 5000 )

/* The keep-alive interval in seconds used for MQTT ping request. */
#define MQTT_KEEP_ALIVE_SECONDS           ( 60 )

/* Every active MQTT connection must have a unique client identifier. If you 
 * are using the above 'MQTT_CLIENT_IDENTIFIER' as client ID for multiple MQTT 
 * connections simultaneously, set this macro to 1. The device will then
 * generate a unique client identifier by appending a timestamp to the 
 * 'MQTT_CLIENT_IDENTIFIER' string. Example: 'psoc6-mqtt-client5927'
 */
#define GENERATE_UNIQUE_CLIENT_ID         ( 1 )

/* The longest client identifier that an MQTT server must accept (as defined
 * by the MQTT 3.1.1 spec) is 23 characters. However some MQTT brokers support 
 * longer client IDs. Configure this macro as per the MQTT broker specification. 
 */
#define MQTT_CLIENT_IDENTIFIER_MAX_LEN    ( 23 )

/* As per Internet Assigned Numbers Authority (IANA) the port numbers assigned 
 * for MQTT protocol are 1883 for non-secure connections and 8883 for secure
 * connections. In some cases there is a need to use other ports for MQTT like
 * port 443 (which is reserved for HTTPS). Application Layer Protocol 
 * Negotiation (ALPN) is an extension to TLS that allows many protocols to be 
 * used over a secure connection. The ALPN ProtocolNameList specifies the 
 * protocols that the client would like to use to communicate over TLS.
 * 
 * This macro specifies the ALPN Protocol Name to be used that is supported
 * by the MQTT broker in use.
 * Note: For AWS IoT, currently "x-amzn-mqtt-ca" is the only supported ALPN 
 *       ProtocolName and it is only supported on port 443.
 * 
 * Uncomment the below line and specify the ALPN Protocol Name to use this 
 * feature.
 */
// #define MQTT_ALPN_PROTOCOL_NAME           "x-amzn-mqtt-ca"

/* Server Name Indication (SNI) is extension to the Transport Layer Security 
 * (TLS) protocol. As required by some MQTT Brokers, SNI typically includes the 
 * hostname in the Client Hello message sent during TLS handshake.
 * 
 * Uncomment the below line and specify the SNI Host Name to use this extension
 * as specified by the MQTT Broker.
 */
//#define MQTT_SNI_HOSTNAME                 "8c57cdc384d84fb390016cf284737f24.s2.eu.hivemq.cloud"

/* A Network buffer is allocated for sending and receiving MQTT packets over 
 * the network. Specify the size of this buffer using this macro.
 * 
 * Note: The minimum buffer size is defined by 'CY_MQTT_MIN_NETWORK_BUFFER_SIZE' 
 * macro in the MQTT library. Please ensure this macro value is larger than 
 * 'CY_MQTT_MIN_NETWORK_BUFFER_SIZE'.
 */
#define MQTT_NETWORK_BUFFER_SIZE          ( 2 * CY_MQTT_MIN_NETWORK_BUFFER_SIZE )

/* Maximum MQTT connection re-connection limit. */
#define MAX_MQTT_CONN_RETRIES            (150u)

/* MQTT re-connection time interval in milliseconds. */
#define MQTT_CONN_RETRY_INTERVAL_MS      (2000)


/**************** MQTT CLIENT CERTIFICATE CONFIGURATION MACROS ****************/

/* Configure the below credentials in case of a secure MQTT connection. */
/* PEM-encoded client certificate */
/*#define CLIENT_CERTIFICATE      \
*"-----BEGIN CERTIFICATE-----\n" \
*"MIIEPTCCAyWgAwIBAgIUBPwcmF6zdQLjykDiTCvo6RzATmowDQYJKoZIhvcNAQEL\n"\
*"BQAwga0xCzAJBgNVBAYTAkJFMRMwEQYDVQQIDApMaW1idXJnDQ0NMRMwEQYDVQQH\n"\
*"DApEaWVwZW5iZWVrMREwDwYDVQQKDAhVSGFzc2VsdDEVMBMGA1UECwwMVWhhc3Nl\n"\
*"bHRfSW9UMRcwFQYDVQQDDA5Kb25hcyBTaWtvcnNraTExMC8GCSqGSIb3DQEJARYi\n"\
*"am9uYXMuc2lrb3Jza2lAc3R1ZGVudC51aGFzc2VsdC5iZTAeFw0yMzEyMDYxMzMy\n"\
*"NTdaFw0yNDEyMDUxMzMyNTdaMIGtMQswCQYDVQQGEwJCRTETMBEGA1UECAwKTGlt\n"\
*"YnVyZw0NDTETMBEGA1UEBwwKRGllcGVuYmVlazERMA8GA1UECgwIVUhhc3NlbHQx\n"\
*"FTATBgNVBAsMDFVoYXNzZWx0X0lvVDEXMBUGA1UEAwwOSm9uYXMgU2lrb3Jza2kx\n"\
*"MTAvBgkqhkiG9w0BCQEWImpvbmFzLnNpa29yc2tpQHN0dWRlbnQudWhhc3NlbHQu\n"\
*"YmUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDRZyAgB2mtZSMQSzTk\n"\
*"fQVw+Am3HcHCEZ3AV8oWKniZwo/HZXCxLoKzEeFTCWXPUJ6cqBaiWAl7Ko+Aw1p/\n"\
*"dqClDoBhlyuD6mQ+TEyXm3ua5+rKuDXDGSlF+zvYQ5x6k4FM4X3KwvJsB21h2nDT\n"\
*"VvM/yn2U3l3gSnBRbko+S5Co1pm/iix6H6DtopMn8WbiWY3p6y0AY2psiVdsAlmO\n"\
*"AmwsKZA1NT3g5RxuQyduS1EkQhgpexv4NxDZLRwTo5gNp4rJszJZg6V3He1njQr5\n"\
*"/TKWte7zCnLFMCpJ2d0w40pYkcISuZ5P/Av5DL22h+C5mVg+4wSjBGlfXj5uK26m\n"\
*"tIzrAgMBAAGjUzBRMB0GA1UdDgQWBBQmKJbTF9Onlqy3/ZWAVLErKbtYmTAfBgNV\n"\
*"HSMEGDAWgBQmKJbTF9Onlqy3/ZWAVLErKbtYmTAPBgNVHRMBAf8EBTADAQH/MA0G\n"\
*"CSqGSIb3DQEBCwUAA4IBAQAa29lmPKSUPdumpzm1zfbwNLZ3ucD4tRJcIFZtIlph\n"\
*"kcjenUiOZAof/izo/DbrqtAXiUqItme39yUMH0NY0226p7ZQc8ceJhlpju/SNSrw\n"\
*"I2VThbOBz0nuMVHrxDYb898c8oM1BKILoSmLkN9PSVw57Hbw1W578+TVrtB/OjQq\n"\
*"RgqUcTx4dfEp95idSIf1V/hMp0HLQEz9K0mX7tKhUAkuTrE82v5IKbVsoEuM0pg0\n"\
*"s+C2AM8GREW52t3gLT7L2+e/6FTnzEznjmK5jH8NpDZmzumCCXpp8w+6ys0rh3Ki\n"\
*"enVSNrvvy/TeYKssLlIrdfaa4wCSQzaijWIwuQkC5P14\n"\
*"-----END CERTIFICATE-----"*/

/* PEM-encoded client private key */
/*#define CLIENT_PRIVATE_KEY          \
*"-----BEGIN RSA PRIVATE KEY-----\n" \
*"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDRZyAgB2mtZSMQ\n"\
*"SzTkfQVw+Am3HcHCEZ3AV8oWKniZwo/HZXCxLoKzEeFTCWXPUJ6cqBaiWAl7Ko+A\n"\
*"w1p/dqClDoBhlyuD6mQ+TEyXm3ua5+rKuDXDGSlF+zvYQ5x6k4FM4X3KwvJsB21h\n"\
*"2nDTVvM/yn2U3l3gSnBRbko+S5Co1pm/iix6H6DtopMn8WbiWY3p6y0AY2psiVds\n"\
*"AlmOAmwsKZA1NT3g5RxuQyduS1EkQhgpexv4NxDZLRwTo5gNp4rJszJZg6V3He1n\n"\
*"jQr5/TKWte7zCnLFMCpJ2d0w40pYkcISuZ5P/Av5DL22h+C5mVg+4wSjBGlfXj5u\n"\
*"K26mtIzrAgMBAAECggEAVVNopzRuDr4NzhdfC5WX8ILZbpi8+Ye1GImNKoAO2VSK\n"\
*"wqymgUQa9L2d63iCWDoZD2t8oZUu89WRWN4BU7vyVJ92l42CKUQKqcnsUcCE2seS\n"\
*"iB0Mpx1rEH2BUqumKNpPDxU47TSHlJZoLz3TyIH/J2iqyEzdwsWCQ+Qlc4HWBb2D\n"\
*"gvSy2fzZKbJ8ShS6Hc5MZ7IW1ws+KNYIzKT8b7VFWiMwmXooYSK3WJr8xzE6CFXf\n"\
*"ZRM1W2BD0rM5b7pXP1CPzIdKu3auCVaEwWEW6hwYNxF5nRkDlzQSbVYgwy0SNkay\n"\
*"cKd13Q4FWwDqObhMNsfOceAqde1UvaaLt6aGviY0PQKBgQDoeKbfAuEdbKV+uCQP\n"\
*"rrPkuvlkb8X9fU8kgvTvVd0hJzXbSn9CNzhxI7pNeaP5ULOxA+LjDFHIBBm5MV5Z\n"\
*"LIOTwMepLM+GmHGRTR4g850+h+/I4pZcVa4g+3TIEH1hq9ugh9uihSMIogDdnwva\n"\
*"xgg2wV+9sXaD6kai1EfCyYz5DwKBgQDmmMSjNt/Yt4il+g/SBvTFRsCZn7LG+8sS\n"\
*"cIPb4Ov9YUX9Qk3bYfBEjPXYVrGZLlrQ+LvsOYP7CzghLxakPprb9Qqy332kHaVT\n"\
*"x0hF+wPNDJE8HL8uTvStyScogeEEvEpL3O/vFeBz9L1017S3xNBYnrMpqnL8VeP6\n"\
*"C2Fg+mEWZQKBgDvOLj/ZIcjMFpdPEBfovebuIxKvnqPkBORDvHeGA2lwCO7tb2e9\n"\
*"hQu2QUuFK6YMGO5FLa1zkeZ/B48ZIEiYpxDv222uVYUu2qiiykl34tAfcJShlkUS\n"\
*"1cUua5C8jUT/TXUy/lIFJkomQ0rAi/AwWhScEuFeMjslnh5ttjhqWZYJAoGBAMlw\n"\
*"NoZlj1Hfsk1bjqpoTTZwQhtxOFk+5/ypsWZIq55idSNx4lV8zsjzYmekA+zOY6Md\n"\
*"RfxrmfGZsWS7n8nGrrzq6HetaDIPe7cd5PLM/lsHWW/rpM6tRmzxxXVLT+g1G6n9\n"\
*"zNNMhxCEgWQqcsH9+gsQR25kaaIo3cg2XNC8qEdJAoGBAN+GzramfvvWPonZTmcO\n"\
*"25cvptpNj/sqnEvcCwjfE7fWEibqpxZYc1NjzZxu1v/lS9rC/AwYbQluiIWX6uWh\n"\
*"Qvaq99eiwb87v5rLiZmcbBwoYO8VJ7JS5Yz7OP4cr+v4TlvAWL7+1ZKjULAr7UQW\n"\
*"FlSAfosQBbE+DdrYAgBTCmpI\n"\
*"-----END RSA PRIVATE KEY-----"*/

/* PEM-encoded Root CA certificate */
/*#define ROOT_CA_CERTIFICATE     \
*"-----BEGIN CERTIFICATE-----\n" \
*"MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n"\
*"TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n"\
*"cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n"\
*"WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n"\
*"ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\n"\
*"MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\n"\
*"h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n"\
*"0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\n"\
*"A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\n"\
*"T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\n"\
*"B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC\n"\
*"B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv\n"\
*"KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn\n"\
*"OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn\n"\
*"jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw\n"\
*"qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI\n"\
*"rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\n"\
*"HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq\n"\
*"hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\n"\
*"ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ\n"\
*"3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK\n"\
*"NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5\n"\
*"ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur\n"\
*"TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC\n"\
*"jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc\n"\
*"oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq\n"\
*"4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA\n"\
*"mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d\n"\
*"emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n"\
*"-----END CERTIFICATE-----"*/


/******************************************************************************
* Global Variables
*******************************************************************************/
extern cy_mqtt_broker_info_t broker_info;
extern cy_awsport_ssl_credentials_t  *security_info;
extern cy_mqtt_connect_info_t connection_info;


#endif /* MQTT_CLIENT_CONFIG_H_ */
